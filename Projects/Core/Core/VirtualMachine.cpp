
// Header
#include "VirtualMachine.h"

// Library includes
#include <iostream>
#include <fstream>

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include <Tools/Files.h>
#include "Analyser.h"
#include "Repository.h"
#include "Scope.h"
#include "Script.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


VirtualMachine::VirtualMachine()
: mRepository(0)
{
	mRepository = new Repository();
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

	result = basefolder + result + ".os";
	return result;
}

Script* VirtualMachine::createScript(const std::string& content, const ParameterList& params)
{
	init();

	Script *script = new Script();
	mScripts.insert(script);

	script->connectRepository(mRepository);

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
	for ( Designtime::BluePrintList::iterator it = objects.begin(); it != objects.end(); ++it ) {
		// add blue prints to our object repository
		mRepository->addBlueprint((*it));

		if ( it->Filename() == mScriptFile && it->Typename() == "Main" ) {
			// create an instance of our Main object
			mObjects.insert(std::make_pair(
				it->Typename(), mRepository->createInstance(it->Typename(), "main")
			));

			ObjectCollection::iterator objIt = mObjects.find(it->Typename());
			assert(objIt != mObjects.end());

			// ... and assign it to our script
			script->assign(objIt->second);
		}
	}

	// execute this script's constructor
	script->construct(params);

	return script;
}

Script* VirtualMachine::createScriptFromFile(const std::string& filename, const ParameterList& params)
{
	OSinfo("processing script '" + filename + "'...");

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
	OSinfo("processing string...");

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
		Extensions::ExtensionMethods methods;
		(*extIt)->provideMethods(methods);

		for (Extensions::ExtensionMethods::const_iterator it = methods.begin(); it != methods.end(); ++it) {
			OSinfo("adding extension '" + (*extIt)->getName() + "." + (*it)->getName() + "'");

			(*it)->setParent(mRepository->getGlobalScope());

			mRepository->getGlobalScope()->defineMethod((*it)->getName(), (*it));
		}
	}

	return true;
}

bool VirtualMachine::loadLibrary(const std::string& library)
{
	OSinfo("loading additional library file '" + library + "'...");

	if ( mImportedLibraries.find(library) != mImportedLibraries.end() ) {
		// circular import => abort
		return true;
	}

	if ( !::Utils::Tools::Files::exists(library) ) {
		return false;
	}

	std::string baseFolder = ::Utils::Tools::Files::ExtractPathname(library);

	try {
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
	catch ( std::exception& e ) {
		OSerror(e.what());
	}

	return false;
}

void VirtualMachine::setBaseFolder(const std::string& base)
{
	if ( base.empty() ) {
		return;
	}

	mBaseFolder = base + "/";

	OSinfo("root = " + mBaseFolder);
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
