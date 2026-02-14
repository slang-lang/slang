
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
#include <Core/Runtime/Script.h>
#include <Logger/Logger.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>
#include <Utils.h>
#include "Controller.h"

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
: mIsInitialized(false)
{
	Controller::Instance().init();
}

VirtualMachine::~VirtualMachine()
{
	for ( auto& script : mScripts ) {
		delete script;
	}
	mScripts.clear();

	Controller::Instance().deinit();

	for ( auto& extension : mExtensions ) {
		delete extension;
	}
	mExtensions.clear();
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

		auto* globalScope = Controller::Instance().globalScope();
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

			method->setParent( globalScope );

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

void VirtualMachine::addLibraryFolder(const std::string& libraryFolder )
{
	if ( libraryFolder .empty() ) {
		return;
	}

#ifdef _MSC_VER
	auto folder = Utils::Tools::Files::GetFullname( libraryFolder  + "/" );
#else
	auto folder = Utils::Tools::Files::GetFullname( libraryFolder  ) + "/";
#endif

	if ( mLibraryFolders.find( folder ) == mLibraryFolders.end() ) {
		mLibraryFolders.insert( folder );
	}
}

Script* VirtualMachine::createScript(const std::string& content)
{
	if ( !mIsInitialized ) {
		init();
	}

	auto* script = new Script();

	mScripts.insert( script );

	Designtime::Analyser analyser( mSettings.DoSanityCheck, mSettings.PrintTokens );
	analyser.processString( content, mScriptFile );

	// load all extension references
	auto extensions = analyser.getExtensionReferences();
	for ( const auto& extension : extensions ) {
		if ( !loadExtension( extension, (*mLibraryFolders.begin()) ) ) {
			throw Common::Exceptions::Exception( "could not load extension '" + extension + "' from '" + (*mLibraryFolders.begin()) + "'" );
		}
	}

	// load all library references
	auto libraryImports = analyser.getLibraryReferences();
	for ( const auto& file : libraryImports ) {
		bool imported{ false };

		for ( const auto& folder : mLibraryFolders ) {
			if ( loadLibrary( buildFilename( folder, file ), mScriptFile ) ) {
				imported = true;
				break;
			}
		}

		if ( !imported ) {
			throw Common::Exceptions::Exception( "could not resolve import '" + file + "'" );
		}
	}

	auto* globalScope = Controller::Instance().globalScope();

	Controller::Instance().repository()->initializeBlueprints();

	Controller::Instance().phase(Controller::Phase::Generation);

	AST::TreeGenerator generator( Controller::Instance().repository(), mSettings.DoCollectErrors );
	generator.process(globalScope);

	auto errors = generator.hasErrors();
	if ( errors ) {
		throw Common::Exceptions::Exception(Utils::Tools::toString(errors) + " error(s) during AST generation detected!");
	}

#ifdef USE_AST_OPTIMIZATION

	Controller::Instance().phase(Controller::Phase::Optimization);

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

	Designtime::Analyser analyser( mSettings.DoSanityCheck, mSettings.PrintTokens );
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

	Controller::Instance().phase(Controller::Phase::Execution);

	MethodScope* globalScope = Controller::Instance().globalScope();

	auto* main = dynamic_cast<Common::Method*>(globalScope->resolveMethod("Main", params, false));
	if ( !main ) {
		throw Common::Exceptions::Exception("could not resolve method 'Main(" + toString(params) + ")'");
	}

	auto* thread = Controller::Instance().threads()->createThread();

	auto controlflow = thread->execute(nullptr, main, params, result);
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


}

namespace {

	std::string buildFilename( const std::string& folder, const std::string& filename ) {
		auto path = Utils::Tools::Files::BuildPath( folder, filename );

		// (1) look for a ".slang" file (new standard)
		auto file = path + ".slang";
		if ( Utils::Tools::Files::exists( file ) ) {
			return file;
		}

		// (2) look for a ".os" file (deprecated)
		file = path + ".os";
		if ( Utils::Tools::Files::exists( file ) ) {
			return file;
		}

		// (3) look for an "All.slang" file (new standard)
		file = Utils::Tools::Files::BuildPath( path, std::string( "/All" ) ) + ".slang";
		if ( Utils::Tools::Files::exists( file ) ) {
			return file;
		}

		// (4) look for an "All.os" file as a last resort (deprecated)
		return Utils::Tools::Files::BuildPath( path, std::string( "/All" ) ) + ".os";
	}

}
