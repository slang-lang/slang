
// Header
#include "VirtualMachine.h"

// Library includes
#include <dirent.h>
#include <fstream>

// Project includes
#include <Core/AST/Generator.h>
#include <Core/AST/TreeGenerator.h>
#include <Core/AST/TreeInterpreter.h>
#include <Core/AST/TreeOptimizer.h>
#include <Core/Common/Exceptions.h>
#include <Core/Defines.h>
#include <Core/Designtime/Analyser.h>
#include <Core/Runtime/Script.h>
#include <Core/Tools.h>
#include <Tools/Files.h>
#include <Tools/Strings.h>
#include <Utils.h>
#include "Controller.h"

// Namespace declarations


namespace ObjectiveScript {


void read_directory(const std::string& dirname, std::vector<std::string>& files)
{
    DIR* dirp = opendir(dirname.c_str());
    struct dirent * dp;

    while ( (dp = readdir(dirp)) != NULL ) {
        std::string file(dp->d_name);

        if ( file != "." && file != ".." ) {
			files.push_back(dirname + "/" + file);
        }
    }

    closedir(dirp);
}


VirtualMachine::VirtualMachine()
: mIsInitialized(false)
{
	Controller::Instance().init();
}

VirtualMachine::~VirtualMachine()
{
	for ( ScriptCollection::iterator it = mScripts.begin(); it != mScripts.end(); ++it ) {
		delete (*it);
	}
	mScripts.clear();

	Controller::Instance().deinit();

	for ( Extensions::ExtensionList::iterator it = mExtensions.begin(); it != mExtensions.end(); ++it ) {
		delete (*it);
	}
}

void VirtualMachine::addExtension(AExtension *extension)
{
	assert(extension);

	mExtensions.push_back(extension);
}

void VirtualMachine::addLibraryFolder(const std::string &library)
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

Script* VirtualMachine::createScript(const std::string& content, bool collectErrors)
{
	if ( !mIsInitialized ) {
		init();
		printLibraryFolders();
	}


	Script *script = new Script();
	mScripts.insert(script);

	Designtime::Analyser analyser(mSettings.DoSanityCheck);
	analyser.processString(content, mScriptFile);

	// load all library references
	StringList libraries = analyser.getLibraryReferences();
	for ( StringList::const_iterator libIt = libraries.begin(); libIt != libraries.end(); ++libIt ) {
		bool imported = false;

		for ( StringSet::const_iterator folderIt = mLibraryFolders.begin(); folderIt != mLibraryFolders.end(); ++folderIt ) {
			std::string filename = Utils::Tools::Files::BuildLibraryPath((*folderIt), (*libIt));

			if ( loadLibrary(filename) ) {
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

	AST::Generator generator(collectErrors);
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

	if ( mSettings.DoSyntaxCheck ) {
		std::cout << "Syntax check done, no errors found." << std::endl;

		throw Runtime::ControlFlow::ExitProgram;
	}

	return script;
}

Script* VirtualMachine::createScriptFromFile(const std::string& filename, bool collectErrors)
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

	return createScript(content, collectErrors);
}

Script* VirtualMachine::createScriptFromString(const std::string& content, bool collectErrors)
{
	OSdebug("processing string...");

	mScriptFile = "";

	return createScript(content, collectErrors);
}

void VirtualMachine::init()
{
	OSdebug("initializing virtual machine...");

	const char* homepath = getenv(OBJECTIVESCRIPT_LIBRARY);
	if ( homepath ) {
		std::string path = std::string(homepath);

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
#else
		std::vector<std::string> sharedLibraries;
		read_directory(SHARED_LIBRARY_DIRECTORY, sharedLibraries);

		// load installed shared libraries
		for ( std::string library : sharedLibraries ) {
			OSdebug("Loading extensions " + library);

			addExtension( mExtensionManager.load(library) );
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

	for ( Extensions::ExtensionList::const_iterator extIt = mExtensions.begin(); extIt != mExtensions.end(); ++extIt ) {
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
			std::cout << "error while loading extension: " << e.what() << std::endl;
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
	for ( std::list<std::string>::const_iterator libIt = libraries.begin(); libIt != libraries.end(); ++libIt ) {
		bool imported = false;

		for ( StringSet::const_iterator folderIt = mLibraryFolders.begin(); folderIt != mLibraryFolders.end(); ++folderIt ) {
			std::string filename = Utils::Tools::Files::BuildLibraryPath((*folderIt), (*libIt));

			if ( loadLibrary(filename) ) {
				imported = true;
				break;
			}
		}

		if ( !imported ) {
			throw Common::Exceptions::Exception("could not resolve import '" + (*libIt) + "'");
		}
	}

	return true;
}

void VirtualMachine::printLibraryFolders()
{
	for ( StringSet::const_iterator it = mLibraryFolders.begin(); it != mLibraryFolders.end(); ++it ) {
		OSdebug("Library: " + (*it));
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

	Runtime::ControlFlow::E controlflow = thread->execute(NULL, main, params, result);
	if ( controlflow == Runtime::ControlFlow::Throw ) {
		throw Runtime::ControlFlow::Throw;
	}
}

void VirtualMachine::runScriptFromFile(const std::string &filename, const ObjectiveScript::ParameterList &params, ObjectiveScript::Runtime::Object *result)
{
	Script* script = createScriptFromFile(filename);

	run(script, params, result);
}

void VirtualMachine::runScriptFromString(const std::string &content, const ObjectiveScript::ParameterList &params, ObjectiveScript::Runtime::Object *result)
{
	Script* script = createScriptFromString(content);

	run(script, params, result);
}

VirtualMachine::Settings& VirtualMachine::settings()
{
	return mSettings;
}


}
