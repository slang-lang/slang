
// Header
#include "VirtualMachine.h"

// Library includes
#ifdef _WIN32
	// Extension loading is not supported under Windows
#else
#include <dirent.h>
#endif
#include <fstream>
#include <vector>

// Project includes
#include <Core/AST/TreeGenerator.h>
#include <Core/Common/Exceptions.h>
#include <Core/Defines.h>
#include <Core/Designtime/Analyser.h>
#include <Core/Script.h>
#include <Core/VirtualMachine/Memory.h>
#include <Core/VirtualMachine/Repository.h>
#include <Logger/Logger.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>
#include <Utils.h>

// Namespace declarations


namespace {
	std::string buildFilename( const std::string& folder, const std::string& filename );
}

namespace Slang {


#ifdef _WIN32
	// Extension loading is not supported under Windows
#else
void read_directory(const std::string& dirname, std::vector<std::string>& files)
{
	DIR* dirp = opendir(dirname.c_str());
	if ( !dirp ) {
		// couldn't opern directory
		return;
	}

	dirent* dp;

	while ( (dp = readdir(dirp)) != nullptr ) {
		std::string file(dp->d_name);

		if ( file != "." && file != ".." ) {
			files.push_back(dirname + "/" + file);
		}
	}

	closedir(dirp);
}
#endif


VirtualMachine::VirtualMachine()
: mGlobalScope(nullptr),
  mMemory(nullptr),
  mPhase(Phase::Startup),
  mRepository(nullptr),
  mThreads(nullptr),
  mIsInitialized(false)
{
	mMemory     = new Memory( this );
	mRepository = new Repository( this );
	mThreads    = new Threads( this );

	initVMComponents();
}

VirtualMachine::~VirtualMachine()
{
	for ( auto& script : mScripts ) {
		delete script;
	}
	mScripts.clear();

	deinitVMComponents();

	for ( auto& extension : mExtensions ) {
		delete extension;
	}

	delete mGlobalScope;
	delete mThreads;
	delete mMemory;
	delete mRepository;
}

bool VirtualMachine::addExtension( Extensions::AExtension* extension, const std::string& library )
{
	if ( !extension ) {
		// provided an invalid extension - ignore it...
		OSerror( "invalid extension '" + library + "' detected!" );

		return false;
	}

	OSdebug( "Loaded extension " + extension->getName() + " version " + extension->getVersion() );

	try {
		OSdebug( "adding extension '" + extension->getName() + "'" );

		auto* globalScope = mGlobalScope;
		Extensions::ExtensionMethods methods;

		extension->initialize( globalScope );
		extension->provideMethods( methods );

		if ( !mSpecification.empty() ) {
			mSpecification.push_back( "" );
		}
		mSpecification.push_back( "Extension " + extension->getName() + ":" );
		mSpecification.push_back( "---" );

		for ( auto& method : methods ) {
			OSdebug( "adding extension method '" + extension->getName() + "." + method->getName() + "'" );

			globalScope->defineMethod( method->getName(), method );

			mSpecification.push_back( method->ToString() );
		}
	}
	catch ( std::exception &e ) {
		OSerror( "error while loading extension: " + std::string( e.what() ) );
	}

	mExtensions.push_back( extension );

	return true;
}

void VirtualMachine::addLibraryFolder(const std::string& library)
{
	if ( library.empty() ) {
		return;
	}

#ifdef _MSC_VER
	mLibraryFolders.insert(Utils::Tools::Files::GetFullname(library + "/"));
#else
	mLibraryFolders.insert(Utils::Tools::Files::GetFullname(library) + "/");
#endif
}

Script* VirtualMachine::createScript(const std::string& content)
{
	if ( !mIsInitialized ) {
		init();
	}

	auto script = new Script(this);
	mScripts.insert(script);

	Designtime::Analyser analyser(this, mSettings.DoSanityCheck, mSettings.PrintTokens);
	analyser.processString(content, mScriptFile);

	// load all extension references
	auto extensions = analyser.getExtensionReferences();
	for ( const auto& ext : extensions ) {
		if ( !loadExtension( ext, (*mLibraryFolders.begin()) ) ) {
			throw Common::Exceptions::Exception( "could not load extension '" + ext + "' from '" + (*mLibraryFolders.begin()) + "'" );
		}
	}

	// load all library references
	auto libraries = analyser.getLibraryReferences();
	for ( auto libIt = libraries.begin(); libIt != libraries.end(); ++libIt ) {
		bool imported = false;

		for ( const auto& libraryFolder : mLibraryFolders ) {
			if ( loadLibrary( buildFilename( libraryFolder, (*libIt) ), mScriptFile ) ) {
				imported = true;
				break;
			}
		}

		if ( !imported ) {
			throw Common::Exceptions::Exception("could not resolve import '" + (*libIt) + "'");
		}
	}

	auto* globalScope = mGlobalScope;

	mRepository->initializeBlueprints();

	mPhase = Phase::Generation;

	AST::TreeGenerator generator( mRepository, mSettings.DoCollectErrors );
	generator.process(globalScope);

	auto errors = generator.hasErrors();
	if ( errors ) {
		throw Common::Exceptions::Exception(Utils::Tools::toString(errors) + " error(s) during AST generation detected!");
	}

#ifdef USE_AST_OPTIMIZATION

	mPhase = Phase::Optimization;

	AST::TreeOptimizer optimizer;
	optimizer.process(globalScope);

#endif

	return script;
}

Script* VirtualMachine::createScriptFromFile(const std::string& filename)
{
	OSdebug("processing script '" + filename + "'...");

	if ( filename.empty() ) {
		OSerror("invalid filename '" + filename + "' provided!");
		throw Common::Exceptions::Exception("invalid filename '" + filename + "' provided!");
	}
	if ( !Utils::Tools::Files::exists(filename) ) {
		OSerror("file '" + filename + "' not found!");
		throw Common::Exceptions::Exception("file '" + filename + "' not found!");
	}

	// open file
	std::ifstream in(filename.c_str(), std::ios_base::binary);

	// read file content
	auto content = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());

	addLibraryFolder(Utils::Tools::Files::ExtractPathname(Utils::Tools::Files::GetFullname(filename)));
	mScriptFile = Utils::Tools::Files::GetFullname(filename);

	return createScript(content);
}

Script* VirtualMachine::createScriptFromString(const std::string& content)
{
	OSdebug("processing string...");

	mScriptFile = "";

	return createScript(content);
}

void VirtualMachine::init()
{
	OSdebug( "initializing virtual machine..." );

	auto* homepath = getenv( SLANG_LIBRARY );
	if ( homepath ) {
		std::string path( homepath );

		while ( !path.empty() ) {
			std::string left;
			std::string right;

			Utils::Tools::splitBy( path, ':', left, right );
			addLibraryFolder( left );

			path = right;
		}
	}

	if ( !mSettings.DoSkipExtensions ) {
#ifdef _WIN32
		// Extension loading is not supported under Windows
#else
		OSdebug( "loading extensions..." );

		std::vector<std::string> sharedLibraries;
		read_directory( SHARED_EXTENSION_DIRECTORY, sharedLibraries );

		// load installed shared libraries
		for ( const std::string& library : sharedLibraries ) {
			addExtension( mExtensionManager.load( library ), library );
		}
#endif
	}

	mIsInitialized = true;
}

bool VirtualMachine::loadExtension( const std::string& extension, const std::string& folder )
{
	auto library = folder + extension;

#if defined __APPLE__
	library += ".dylib";
#elif defined __linux
	library += ".so";
#endif

#if defined _MSC_VER
	OSerror("Extension loading is not support under your OS!");

	return false;
#else
	OSdebug( "Loading extension '" + library + "'" );

	return addExtension( mExtensionManager.load( library ), library );
#endif
}

bool VirtualMachine::loadLibrary(const std::string& library, const std::string& fromLibrary)
{
	OSdebug( "loading library file '" + library + "' from file '" + fromLibrary + "'..." );

	if ( !Utils::Tools::Files::exists( library ) ) {
		// provided library file doesn't exist!
		return false;
	}

	if ( mImportedLibraries.find( library ) != mImportedLibraries.end() ) {
		OSdebug( "Ignoring already imported file '" + library + "'" );
		return true;
	}

	auto currentFolder = Utils::Tools::Files::ExtractPathname( library );
	addLibraryFolder( currentFolder );

	mImportedLibraries.insert( library );

	Designtime::Analyser analyser( this, mSettings.DoSanityCheck, mSettings.PrintTokens );
	analyser.processFile( library );

	// load all extension references
	auto extensions = analyser.getExtensionReferences();
	for ( const auto& extension : extensions ) {
		if ( !loadExtension( extension, currentFolder ) ) {
			throw Common::Exceptions::Exception( "could not load extension '" + extension + "' from '" + currentFolder + "'" );
		}
	}

	auto librariesFolders = mLibraryFolders;
	librariesFolders.insert( librariesFolders.begin(), currentFolder );

	// load all library references
	auto libraryImports = analyser.getLibraryReferences();

	// (1) first try to resolve relative to the current file
	for ( auto libIt = libraryImports.begin(); libIt != libraryImports.end(); ) {
		if ( loadLibrary( buildFilename( currentFolder, *libIt ), library ) ) {
			libIt = libraryImports.erase( libIt );
		}
		else {
			++libIt;
		}
	}

	// (2) then try to resolve via the library folders
	for ( const auto& file : libraryImports ) {
		bool imported{ false };

		for ( const auto& folder : librariesFolders ) {
			if ( loadLibrary( buildFilename( folder, file ), library ) ) {
				imported = true;
				break;
			}
		}

		if ( !imported ) {
			throw Common::Exceptions::Exception( "could not resolve import '" + file + "' in file '" + library + "'" );
		}
	}

	return true;
}

void VirtualMachine::printExtensions()
{
	std::cout << std::endl;
	std::cout << "Extensions:" << std::endl;

	for ( const auto& extension : mExtensions ) {
		std::cout << extension->getName();

		if ( !extension->getVersion().empty() ) {
			std::cout << " version " << extension->getVersion();
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

void VirtualMachine::printLibraryFolders()
{
	std::cout << "Libraries:" << std::endl;

	for ( const auto& libraryFolder : mLibraryFolders ) {
		std::cout << libraryFolder << std::endl;
	}
}

void VirtualMachine::printSpecification( const std::string& specification )
{
	if ( specification.empty() ) {
		for ( const auto& str : mSpecification ) {
			std::cout << str << std::endl;
		}

		return;
	}

	int32_t found{ 0 };
	for ( const auto& str : mSpecification ) {
		if ( str.find( specification ) != std::string::npos ) {
            std::cout << str << std::endl;

            found++;
		}
	}

	if ( found ) {
		//std::cout << std::endl;
		//std::cout << "found " << found << " occurrence(s) of " << specification << std::endl;
	}
	else {
		std::cout << "no result found for '" << specification << "'" << std::endl;
	}
}

void VirtualMachine::run(Script* script, const ParameterList& params, Runtime::Object* result)
{
	if ( !script ) {
		throw Common::Exceptions::Exception("provided invalid script to run!");
	}

	mPhase = Phase::Execution;

	MethodScope* globalScope = mGlobalScope;

	auto* main = dynamic_cast<Common::Method*>(globalScope->resolveMethod("Main", params, false));
	if ( !main ) {
		throw Common::Exceptions::Exception("could not resolve method 'Main(" + toString(params) + ")'");
	}

	auto* thread = mThreads->createThread();

	auto controlflow = thread->execute( main, params, result );
	if ( controlflow == Runtime::ControlFlow::Throw ) {
		throw Runtime::ControlFlow::Throw;
	}
}

void VirtualMachine::runScriptFromFile(const std::string &filename, const ParameterList &params, Runtime::Object *result)
{
	auto* script = createScriptFromFile(filename);

	run(script, params, result);
}

void VirtualMachine::runScriptFromString(const std::string &content, const ParameterList &params, Runtime::Object *result)
{
	auto* script = createScriptFromString(content);

	run(script, params, result);
}

VirtualMachine::Settings& VirtualMachine::settings()
{
	return mSettings;
}

void VirtualMachine::initVMComponents()
{
	assert(mPhase == Phase::Startup);

	assert(!mGlobalScope);
	mGlobalScope = new Common::Namespace(VALUE_NONE, nullptr);

	mMemory->init();
	mRepository->init();
	mThreads->init();

	mPhase = Phase::Preparation;
}

void VirtualMachine::deinitVMComponents()
{
	mPhase = Phase::Shutdown;

	mMemory->deinit();
	mThreads->deinit();
	mRepository->deinit();
}

VirtualMachine::Phase::E VirtualMachine::phase() const
{
	return mPhase;
}

Common::Namespace* VirtualMachine::globalScope() const
{
	return mGlobalScope;
}

Memory* VirtualMachine::memory() const
{
	return mMemory;
}

Repository* VirtualMachine::repository() const
{
	return mRepository;
}

Thread* VirtualMachine::thread(ThreadId id) const
{
	return mThreads->getThread(id);
}

Threads* VirtualMachine::threads() const
{
	return mThreads;
}


}

namespace {
	std::string buildFilename( const std::string& folder, const std::string& filename ) {
		// (1) look for a ".slang" file (new standard)
		auto file = Utils::Tools::Files::BuildPath( folder, filename ) + ".slang";
		if ( Utils::Tools::Files::exists( file ) ) {
			return file;
		}

		// (2) look for a ".os" file (deprecated)
		file = Utils::Tools::Files::BuildPath( folder, filename ) + ".os";
		if ( Utils::Tools::Files::exists( file ) ) {
			return file;
		}

		// (3) look for an "All.slang" file (new standard)
		file = Utils::Tools::Files::BuildPath( folder, filename + std::string( "/All" ) ) + ".slang";
		if ( Utils::Tools::Files::exists( file ) ) {
			return file;
		}

		// (4) look for an "All.os" file as a last resort (deprecated)
		return Utils::Tools::Files::BuildPath( folder, filename + std::string( "/All" ) ) + ".os";
	}
}
