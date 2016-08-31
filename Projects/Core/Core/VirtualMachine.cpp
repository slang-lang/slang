
// Header
#include "VirtualMachine.h"

// Library includes
#include <fstream>

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include <Tools/Files.h>
#include "Analyser.h"
#include "Consts.h"
#include "Repository.h"
#include "Script.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


VirtualMachine::VirtualMachine()
{
	mRepository = new Repository();
}

VirtualMachine::~VirtualMachine()
{
	for ( Extensions::ExtensionList::iterator it = mExtensions.begin(); it != mExtensions.end(); ++it ) {
		delete (*it);
	}
	for ( ScriptCollection::iterator it = mScripts.begin(); it != mScripts.end(); ++it ) {
		delete (*it);
	}
	mScripts.clear();

	delete mRepository;
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
	unsigned long npos = std::string::npos;

	do {
		npos = result.find_first_of(".");
		if ( npos != std::string::npos ) {
			result[npos] = '/';
		}
	} while ( npos != std::string::npos );

	return basefolder + result + ".os";
}

Script* VirtualMachine::createScript(const std::string& content, const ParameterList& params)
{
	init();

	Script *script = new Script(mRepository->getGlobalScope());
	mScripts.insert(script);

	Analyser analyser(mRepository);
	analyser.processString(content, mScriptFile);

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
			throw Utils::Exceptions::Exception("could not resolve import '" + (*libIt) + "'");
		}
	}

/*	Not part of this release
	PrototypeList prototypes = analyser.getPrototypes();
	for ( PrototypeList::iterator it = prototypes.begin(); it != prototypes.end(); ++it ) {
		mRepository->addPrototype((*it));
	}
*/

	// rebuild all blue prints to update/retype their type declarations
	mRepository->rebuildBluePrints();

	// initialize Main object
	Symbol* mainSymbol = mRepository->getGlobalScope()->resolve("Main");
	if ( mainSymbol && mainSymbol->getSymbolType() == Symbol::IType::BluePrintObjectSymbol ) {
		// create an instance of our Main object ...
		Runtime::Object *main = mRepository->createInstance(static_cast<Designtime::BluePrintObject*>(mainSymbol), "main", true);
		assert(main);

		// ... define it in our global scope ...
		mRepository->getGlobalScope()->define("main", main);

		Runtime::ControlFlow::E controlflow = main->Constructor(params);
		if ( controlflow == Runtime::ControlFlow::Throw ) {
			throw Utils::Exceptions::Exception("Exception raised in " + main->getFullScopeName() + "." + main->QualifiedTypename());
		}
	}

	return script;
}

Script* VirtualMachine::createScriptFromFile(const std::string& filename, const ParameterList& params)
{
	OSdebug("processing script '" + filename + "'...");

	if ( filename.empty() ) {
		OSerror("invalid filename '" + filename + "' provided!");
		throw Utils::Exceptions::Exception("invalid filename '" + filename + "' provided!");
	}
	if ( !::Utils::Tools::Files::exists(filename) ) {
		OSerror("file '" + filename + "' not found!");
		throw Utils::Exceptions::Exception("file '" + filename + "' not found!");
	}

	// read file content
	std::ifstream in(filename.c_str(), std::ios_base::binary);

	std::string content = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());

	addLibraryFolder(::Utils::Tools::Files::ExtractPathname(filename));
	mScriptFile = filename;

	return createScript(content, params);
}

Script* VirtualMachine::createScriptFromString(const std::string& content, const ParameterList& params)
{
	OSdebug("processing string...");

	mScriptFile = "";

	return createScript(content, params);
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

			(*extIt)->initialize(mRepository->getGlobalScope());

			Extensions::ExtensionMethods methods;
			(*extIt)->provideMethods(methods);

			MethodScope* scope = mRepository->getGlobalScope();

			for ( Extensions::ExtensionMethods::const_iterator it = methods.begin(); it != methods.end(); ++it ) {
				OSdebug("adding extension '" + (*extIt)->getName() + "." + (*it)->getName() + "'");

				(*it)->setParent(scope);
				(*it)->setRepository(mRepository);

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
		OSinfo("circular imports detected in file '" + library + "'");
		return true;
	}

	mLibraryFolders.insert(::Utils::Tools::Files::ExtractPathname(library));

	Analyser analyser(mRepository);
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
			throw Utils::Exceptions::Exception("could not resolve import '" + (*libIt) + "'");
		}
	}

/*	Not part of this release
	PrototypeList prototypes = analyser.getPrototypes();
	for ( PrototypeList::iterator it = prototypes.begin(); it != prototypes.end(); ++it ) {
		mRepository->addPrototype((*it));
	}
*/

	return true;
}

void VirtualMachine::printLibraryFolders()
{
	for ( StringSet::const_iterator it = mLibraryFolders.begin(); it != mLibraryFolders.end(); ++it ) {
		OSinfo("Library: " + (*it));
	}
}


}
