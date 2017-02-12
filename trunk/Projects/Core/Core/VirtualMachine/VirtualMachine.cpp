
// Header
#include "VirtualMachine.h"

// Library includes
#include <fstream>

// Project includes
#include <Core/AST/Generator.h>
#include <Core/AST/TreeGenerator.h>
#include <Core/AST/TreeInterpreter.h>
#include <Core/Common/Exceptions.h>
#include <Core/Defines.h>
#include <Core/Designtime/Analyser.h>
#include <Core/Runtime/Script.h>
#include <Core/Tools.h>
#include <Tools/Files.h>
#include <Utils.h>
#include "Controller.h"

// Namespace declarations


namespace ObjectiveScript {


VirtualMachine::VirtualMachine()
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

void VirtualMachine::addExtension(Extensions::AExtension *extension)
{
	assert(extension);

	mExtensions.push_back(extension);
}

void VirtualMachine::addLibraryFolder(const std::string &library)
{
	if ( library.empty() ) {
		return;
	}

	mLibraryFolders.insert(library + "/");
}

std::string VirtualMachine::buildPath(const std::string& basefolder, const std::string& library) const
{
	std::string result = library;
	unsigned long npos;// = std::string::npos;

	do {
		npos = result.find_first_of(".");
		if ( npos != std::string::npos ) {
			result[npos] = '/';
		}
	} while ( npos != std::string::npos );

	return basefolder + result + ".os";
}

Script* VirtualMachine::createScript(const std::string& content, const ParameterList& params, Runtime::Object* result)
{
	init();

	Script *script = new Script();
	mScripts.insert(script);

	Designtime::Analyser analyser;
	analyser.processString(content, mScriptFile);

	// load all library references
	StringList libraries = analyser.getLibraryReferences();
	for ( StringList::const_iterator libIt = libraries.begin(); libIt != libraries.end(); ++libIt ) {
		bool imported = false;

		for ( StringSet::const_iterator folderIt = mLibraryFolders.begin(); folderIt != mLibraryFolders.end(); ++folderIt ) {
			std::string filename = buildPath((*folderIt), (*libIt));

			if ( loadLibrary(filename) ) {
				imported = true;
				break;
			}
		}

		if ( !imported ) {
			throw Common::Exceptions::Exception("could not resolve import '" + (*libIt) + "'");
		}
	}

	// Startup
	Common::Method* main = dynamic_cast<Common::Method*>(Controller::Instance().stack()->globalScope()->resolveMethod("Main", params, false));
	if ( !main ) {
		throw Common::Exceptions::Exception("could not resolve method 'Main(" + toString(params) + ")'");
	}

#ifdef GENERATE_PARSE_TREE

	AST::Generator generator;
	generator.process(Controller::Instance().stack()->globalScope());

	AST::TreeInterpreter ti;
	Runtime::ControlFlow::E controlflow = ti.execute(main, params, result);

#else

	Runtime::Interpreter interpreter;
	Runtime::ControlFlow::E controlflow = interpreter.execute(main, params, result);

#endif

	if ( controlflow == Runtime::ControlFlow::Throw ) {
		Runtime::ExceptionData data = Controller::Instance().stack()->exception();

		std::string text = "Exception raised in " + data.getPosition().toString() + ":\n";
					text += data.getData()->ToString();

		throw Common::Exceptions::Exception(text);
	}

	return script;
}

Script* VirtualMachine::createScriptFromFile(const std::string& filename, const ParameterList& params, Runtime::Object* result)
{
	OSdebug("processing script '" + filename + "'...");

	if ( filename.empty() ) {
		OSerror("invalid filename '" + filename + "' provided!");
		throw Common::Exceptions::Exception("invalid filename '" + filename + "' provided!");
	}
	if ( !::Utils::Tools::Files::exists(filename) ) {
		OSerror("file '" + filename + "' not found!");
		throw Common::Exceptions::Exception("file '" + filename + "' not found!");
	}

	// read file content
	std::ifstream in(filename.c_str(), std::ios_base::binary);

	std::string content = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());

	addLibraryFolder(::Utils::Tools::Files::ExtractPathname(filename));
	mScriptFile = filename;

	return createScript(content, params, result);
}

Script* VirtualMachine::createScriptFromString(const std::string& content, const ParameterList& params, Runtime::Object* result)
{
	OSdebug("processing string...");

	mScriptFile = "";

	return createScript(content, params, result);
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

			Tools::splitBy(path, ':', left, right);
			addLibraryFolder(left);

			path = right;
		}
	}

	loadExtensions();

	printLibraryFolders();
}

bool VirtualMachine::loadExtensions()
{
	OSdebug("loading extensions...");

	for ( Extensions::ExtensionList::const_iterator extIt = mExtensions.begin(); extIt != mExtensions.end(); ++extIt ) {
		try {
			OSdebug("adding extension '" + (*extIt)->getName() + "'");

			(*extIt)->initialize(Controller::Instance().stack()->globalScope());

			Extensions::ExtensionMethods methods;
			(*extIt)->provideMethods(methods);

			MethodScope* scope = Controller::Instance().stack()->globalScope();

			for ( Extensions::ExtensionMethods::const_iterator it = methods.begin(); it != methods.end(); ++it ) {
				OSdebug("adding extension '" + (*extIt)->getName() + "." + (*it)->getName() + "'");

				(*it)->setParent(scope);

				scope->defineMethod((*it)->getName(), (*it));
			}
		}
		catch ( std::exception &e ) {
			std::cout << "error while loading extensions: " << e.what() << std::endl;
		}
	}

	return true;
}

bool VirtualMachine::loadLibrary(const std::string& library)
{
	OSdebug("loading library file '" + library + "'...");

	if ( !::Utils::Tools::Files::exists(library) ) {
		// provided library file doesn't exist!
		return false;
	}

	if ( mImportedLibraries.find(library) != mImportedLibraries.end() ) {
		// circular import => abort
		OSdebug("circular imports detected in file '" + library + "'");
		return true;
	}

	mLibraryFolders.insert(::Utils::Tools::Files::ExtractPathname(library));

	Designtime::Analyser analyser;
	analyser.processFile(library);

	mImportedLibraries.insert(library);

	const std::list<std::string>& libraries = analyser.getLibraryReferences();
	for ( std::list<std::string>::const_iterator libIt = libraries.begin(); libIt != libraries.end(); ++libIt ) {
		bool imported = false;

		for ( StringSet::const_iterator folderIt = mLibraryFolders.begin(); folderIt != mLibraryFolders.end(); ++folderIt ) {
			std::string filename = buildPath((*folderIt), (*libIt));

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


}
