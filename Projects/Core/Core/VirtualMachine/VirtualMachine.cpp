
// Header
#include "VirtualMachine.h"

// Library includes
#ifdef _WIN32
	// Extension loading is not supported under Windows
#else
#include <dirent.h>
#endif
#include <fstream>

// Project includes
#include <Core/AST/Generator.h>
#include <Core/Common/Exceptions.h>
#include <Core/Defines.h>
#include <Core/Designtime/Analyser.h>
#include <Core/Runtime/Script.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>
#include <Utils.h>
#include "Controller.h"

// Namespace declarations


namespace {
	std::string buildFilename( std::string folder, std::string filename );
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

    struct dirent * dp;

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
}

void VirtualMachine::addExtension(Extensions::AExtension* extension, const std::string& library)
{
	if ( !extension ) {
		// provided an invalid extension - ignore it...
		OSerror( "invalid extension '" + library + "' detected!" );

		return;
	}

	OSdebug( "Loaded extension " + extension->getName() + " version " + extension->getVersion() );

	mExtensions.push_back( extension );
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

	auto *script = new Script();
	mScripts.insert(script);

	Designtime::Analyser analyser(mSettings.DoSanityCheck);
	analyser.processString(content, mScriptFile);

	// load all library references
	StringList libraries = analyser.getLibraryReferences();
	for ( StringList::const_iterator libIt = libraries.begin(); libIt != libraries.end(); ++libIt ) {
		bool imported = false;

		for ( const auto& libraryFolder : mLibraryFolders ) {
			if ( loadLibrary( buildFilename( libraryFolder, (*libIt) ) ) ) {
				imported = true;
				break;
			}
		}

		if ( !imported ) {
			throw Common::Exceptions::Exception("could not resolve import '" + (*libIt) + "'");
		}
	}

	MethodScope* globalScope = Controller::Instance().globalScope();

	Controller::Instance().repository()->initializeBlueprints();

	Controller::Instance().phase(Controller::Phase::Generation);

	AST::Generator generator(mSettings.DoCollectErrors);
	generator.process(globalScope);

	int errors = generator.hasErrors();
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
	std::string content = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());

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
	OSdebug("initializing virtual machine...");

	auto* homepath = getenv(SLANG_LIBRARY);
	if ( homepath ) {
		std::string path(homepath);

		while ( !path.empty() ) {
			std::string left;
			std::string right;

			Utils::Tools::splitBy(path, ':', left, right);
			addLibraryFolder(left);

			path = right;
		}
	}

	if ( !mSettings.DoSkipExtensions ) {
#ifdef _WIN32
		// Extension loading is not supported under Windows
#else
		std::vector<std::string> sharedLibraries;
		read_directory(SHARED_LIBRARY_DIRECTORY, sharedLibraries);

		// load installed shared libraries
		for ( const std::string& library : sharedLibraries ) {
			addExtension( mExtensionManager.load(library), library );
		}
#endif
	}

	loadExtensions();

	mIsInitialized = true;
}

bool VirtualMachine::loadExtensions()
{
	OSdebug("loading extensions...");

	MethodScope* globalScope = Controller::Instance().globalScope();

	for (Extensions::ExtensionCollection::const_iterator extIt = mExtensions.begin(); extIt != mExtensions.end(); ++extIt ) {
		try {
			OSdebug("adding extension '" + (*extIt)->getName() + "'");

			(*extIt)->initialize(globalScope);

			Extensions::ExtensionMethods methods;
			(*extIt)->provideMethods(methods);

			for ( Extensions::ExtensionMethods::const_iterator it = methods.begin(); it != methods.end(); ++it ) {
				OSdebug("adding extension method '" + (*extIt)->getName() + "." + (*it)->getName() + "'");

				(*it)->setParent(globalScope);

				globalScope->defineMethod((*it)->getName(), (*it));
			}
		}
		catch ( std::exception &e ) {
			OSerror( "error while loading extension: " + std::string( e.what() ) );
		}
	}

	return true;
}

bool VirtualMachine::loadLibrary(const std::string& library)
{
	OSdebug("loading library file '" + library + "'...");

	if ( !Utils::Tools::Files::exists(library) ) {
		// provided library file doesn't exist!
		return false;
	}

	if ( mImportedLibraries.find(library) != mImportedLibraries.end() ) {
		// circular import => abort
		OSdebug("circular imports detected in file '" + library + "'");
		return true;
	}

	mLibraryFolders.insert(Utils::Tools::Files::ExtractPathname(library));

	Designtime::Analyser analyser(mSettings.DoSanityCheck);
	analyser.processFile(library);

	mImportedLibraries.insert(library);

	const std::list<std::string>& libraries = analyser.getLibraryReferences();
	for ( const auto& lib : libraries ) {
		bool imported = false;

		for ( const auto& libraryFolder : mLibraryFolders ) {
			if ( loadLibrary( buildFilename( libraryFolder, lib ) ) ) {
				imported = true;
				break;
			}
		}

		if ( !imported ) {
			throw Common::Exceptions::Exception("could not resolve import '" + lib + "'");
		}
	}

	return true;
}

void VirtualMachine::printExtensions()
{
	std::cout << std::endl;
	std::cout << "Extensions:" << std::endl;

	for ( const auto& extension : mExtensions ) {
		std::cout << extension->getName() << " version " << extension->getVersion() << std::endl;
	}

	std::cout << std::endl;
}

void VirtualMachine::printLibraryFolders()
{
	std::cout << std::endl;

	for ( const auto& libraryFolder : mLibraryFolders ) {
		std::cout << "Library: " + libraryFolder << std::endl;
	}
}

void VirtualMachine::run(Script* script, const ParameterList& params, Runtime::Object* result)
{
	if ( !script ) {
		throw Common::Exceptions::Exception("provided invalid script to run!");
	}

	Controller::Instance().phase(Controller::Phase::Execution);

	MethodScope* globalScope = Controller::Instance().globalScope();

	Common::Method* main = dynamic_cast<Common::Method*>(globalScope->resolveMethod("Main", params, false));
	if ( !main ) {
		throw Common::Exceptions::Exception("could not resolve method 'Main(" + toString(params) + ")'");
	}

	Thread* thread = Controller::Instance().threads()->createThread();

	Runtime::ControlFlow::E controlflow = thread->execute(nullptr, main, params, result);
	if ( controlflow == Runtime::ControlFlow::Throw ) {
		throw Runtime::ControlFlow::Throw;
	}
}

void VirtualMachine::runScriptFromFile(const std::string &filename, const Slang::ParameterList &params, Slang::Runtime::Object *result)
{
	Script* script = createScriptFromFile(filename);

	run(script, params, result);
}

void VirtualMachine::runScriptFromString(const std::string &content, const Slang::ParameterList &params, Slang::Runtime::Object *result)
{
	Script* script = createScriptFromString(content);

	run(script, params, result);
}

VirtualMachine::Settings& VirtualMachine::settings()
{
	return mSettings;
}


}

namespace {
	std::string buildFilename( std::string folder, std::string filename ) {
		std::string all = Utils::Tools::Files::BuildLibraryPath( folder, filename + std::string( "/All" ) );
		if ( Utils::Tools::Files::exists( all ) ) {
			return all;
		}

		return Utils::Tools::Files::BuildLibraryPath( folder, filename );
	}
}

