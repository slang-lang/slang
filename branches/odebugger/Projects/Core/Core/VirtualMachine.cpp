
// Header
#include "VirtualMachine.h"

// Library includes
#include <stdlib.h>
#include <iostream>
#include <fstream>

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include <Tools/Files.h>
#include "Analyser.h"
#include "Repository.h"
#include "Script.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


VirtualMachine::VirtualMachine()
: mRepository(new Repository())
{
}

VirtualMachine::~VirtualMachine()
{
	mBluePrints.clear();
	mObjects.clear();

	for ( Extensions::ExtensionList::iterator it = mExtensions.begin(); it != mExtensions.end(); ++it ) {
		delete (*it);
	}
	for ( ScriptCollection::iterator it = mScripts.begin(); it != mScripts.end(); ++it ) {
		delete (*it);
	}
	mScripts.clear();

	delete mRepository;
}

void VirtualMachine::addExtension(Extensions::IExtension *extension)
{
	assert(extension);

	mExtensions.push_back(extension);
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

	Script *script = new Script(mRepository);
	mScripts.insert(script);

	Analyser analyser(mRepository);
	analyser.processString(content, mScriptFile);

	StringList libraries = analyser.getLibraryReferences();
	for ( StringList::const_iterator it = libraries.begin(); it != libraries.end(); ++it ) {
		std::string filename = buildPath(mBaseFolder, (*it));

		if ( !loadLibrary(filename) ) {
			filename = buildPath(mLibraryFolder, (*it));

			if ( !loadLibrary(filename) ) {
				throw Utils::Exceptions::Exception("could not resolve import '" + (*it) + "'");
			}
		}
	}

/*	Not part of this release
	PrototypeList prototypes = analyser.getPrototypes();
	for ( PrototypeList::iterator it = prototypes.begin(); it != prototypes.end(); ++it ) {
		mRepository->addPrototype((*it));
	}
*/

	Designtime::BluePrintList objects = analyser.getBluePrints();
	Designtime::BluePrintList::iterator mainIt = objects.end();

	for ( Designtime::BluePrintList::iterator it = objects.begin(); it != objects.end(); ++it ) {
		// add blue prints to our object repository
		mRepository->addBlueprint((*it));

		// collect Main object if there is any
		if ( it->Filename() == mScriptFile && it->Typename() == "Main" ) {
			mainIt = it;
		}
	}

	// rebuild all blue prints to update/retype their type declarations
	mRepository->rebuildBluePrints();

	// initialize Main object
	if ( mainIt != objects.end() ) {
		// create an instance of our Main object ...
		Runtime::Object *main = mRepository->createInstance(mainIt->Typename(), "main");
		assert(main);

		// ... define it in our global scope ...
		mRepository->getGlobalScope()->define("main", main);

		Runtime::ControlFlow::E controlflow = main->Constructor(params);
		if ( controlflow == Runtime::ControlFlow::Throw ) {
			throw Utils::Exceptions::Exception("Exception raised in " + main->getFullName() + "::" + main->Typename());
		}

		// ... and store it
		mObjects.insert(std::make_pair(mainIt->Typename(), main));
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

	mBaseFolder = ::Utils::Tools::Files::ExtractPathname(filename);
	mScriptFile = filename;

	// read file content
	std::ifstream in(filename.c_str(), std::ios_base::binary);

	std::string content = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());

	return createScript(content, params);
}

Script* VirtualMachine::createScriptFromString(const std::string& content, const ParameterList& params)
{
	OSdebug("processing string...");

	mBaseFolder = "";
	mScriptFile = "";

	return createScript(content, params);
}

void VirtualMachine::init()
{
	if ( !mLibraryFolder.empty() ) {
		return;
	}

	const char* homepath = getenv("OBJECTIVESCRIPT_LIBRARY");
	if ( homepath ) {
		setLibraryFolder(homepath);
	}

	loadExtensions();
}

bool VirtualMachine::loadExtensions()
{
	for (Extensions::ExtensionList::const_iterator extIt = mExtensions.begin(); extIt != mExtensions.end(); ++extIt) {
		try {
			Extensions::ExtensionMethods methods;
			(*extIt)->provideMethods(methods);

			for (Extensions::ExtensionMethods::const_iterator it = methods.begin(); it != methods.end(); ++it) {
				OSdebug("adding extension '" + (*extIt)->getName() + "." + (*it)->getName() + "'");

				(*it)->setParent(mRepository->getGlobalScope());
				(*it)->setRepository(mRepository);

				mRepository->getGlobalScope()->defineMethod((*it)->getName(), (*it));
			}
		}
		catch ( ... ) {
			std::cout << "error while loading extensions" << std::endl;
		}
	}

	return true;
}

bool VirtualMachine::loadLibrary(const std::string& library)
{
	OSdebug("loading additional library file '" + library + "'...");

	if ( !::Utils::Tools::Files::exists(library) ) {
		// provided library file doesn't exist!
		return false;
	}

	if ( mImportedLibraries.find(library) != mImportedLibraries.end() ) {
		// circular import => abort
		OSinfo("circular imports detected in file '" + library + "'");
		return true;
	}

	std::string baseFolder = ::Utils::Tools::Files::ExtractPathname(library);

	Analyser analyser(mRepository);
	analyser.processFile(library);

	mImportedLibraries.insert(library);

	const std::list<std::string>& libraries = analyser.getLibraryReferences();
	for ( std::list<std::string>::const_iterator it = libraries.begin(); it != libraries.end(); ++it ) {
		std::string filename = buildPath(baseFolder, (*it));

		if ( !loadLibrary(filename) ) {
			filename = buildPath(mLibraryFolder, (*it));

			if ( !loadLibrary(filename) ) {
				throw Utils::Exceptions::Exception("could not resolve import '" + (*it) + "'");
			}
		}
	}

/*	Not part of this release
	PrototypeList prototypes = analyser.getPrototypes();
	for ( PrototypeList::iterator it = prototypes.begin(); it != prototypes.end(); ++it ) {
		mRepository->addPrototype((*it));
	}
*/

	Designtime::BluePrintList blueprints = analyser.getBluePrints();
	for ( Designtime::BluePrintList::iterator it = blueprints.begin(); it != blueprints.end(); ++it ) {
		mRepository->addBlueprint((*it));
	}

	return true;
}

void VirtualMachine::setBaseFolder(const std::string& base)
{
	if ( base.empty() ) {
		return;
	}

	mBaseFolder = base + "/";

	OSinfo("interpreter root = " + mBaseFolder);
}

void VirtualMachine::setLibraryFolder(const std::string& library)
{
	if ( library.empty() ) {
		return;
	}

	mLibraryFolder = library + "/";

	OSinfo("library root = " + mLibraryFolder);
}


}
