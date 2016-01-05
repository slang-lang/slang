
// Header
#include "VirtualMachine.h"

// Library includes

// Project includes
#include <Core/Utils/Utils.h>
#include "Analyser.h"
#include "Memory.h"
#include "Repository.h"
#include "Script.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


VirtualMachine::VirtualMachine()
: mBaseFolder(""),
  mMemory(0),
  mRepository(0),
  mScope(0)
{
	mMemory = new Memory();
	mRepository = new Repository(mMemory);
	mScope = new GlobalScope();
}

VirtualMachine::~VirtualMachine()
{
	mBluePrints.clear();
	mInterfaces.clear();
	mObjects.clear();

	for ( ScriptCollection::iterator it = mScripts.begin(); it != mScripts.end(); ++it ) {
		delete (*it);
	}
	mScripts.clear();

	delete mScope;
	delete mRepository;
	delete mMemory;
}

std::string VirtualMachine::buildLibraryPath(const std::string& library) const
{
	std::string result = library;
	unsigned long npos = std::string::npos;

	do {
		npos = result.find_first_of(".");
		if ( npos != std::string::npos ) {
			result[npos] = '/';
		}
	} while ( npos != std::string::npos );

	result = mBaseFolder + result + ".os";
	return result;
}

Script* VirtualMachine::create(const std::string& filename, const ParameterList& params)
{
	OSinfo("processing script '" + filename + "'...");

	init();

	if ( filename.empty() ) {
		OSwarn("invalid filename '" + filename + "' provided!");
		return 0;
	}

	Script *script = new Script();
	mScripts.insert(script);

	script->connectRepository(mRepository);

	Analyser analyser(mScope);
	analyser.process(filename);

	StringList libraries = analyser.getLibraryReferences();
	for ( StringList::const_iterator it = libraries.begin(); it != libraries.end(); ++it ) {
		loadLibrary((*it));
	}

/*	Not part of this release
	InterfaceList interfaces = analyser.getInterfaces();
	for ( InterfaceList::iterator it = interfaces.begin(); it != interfaces.end(); ++it ) {
		mInterfaces.insert(std::make_pair(
			it->Typename(), (*it)
		));
	}
*/

/*	Not part of this release
	PrototypeList prototypes = analyser.getPrototypes();
	for ( PrototypeList::iterator it = prototypes.begin(); it != prototypes.end(); ++it ) {
		mRepository->addPrototype((*it));
	}
*/

	BluePrintList objects = analyser.getBluePrints();
	for ( BluePrintList::iterator it = objects.begin(); it != objects.end(); ++it ) {
		// add blue prints to our object repository
		mRepository->addBlueprint((*it));

		if ( it->Filename() == filename && it->Typename() == "Main" ) {
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

void VirtualMachine::init()
{
	if ( mBaseFolder.empty() ) {
		const char* homepath = getenv("OBJECTIVESCRIPT_HOME");
		if ( homepath ) {
			setBaseFolder(homepath);
		}
	}
}

void VirtualMachine::loadLibrary(const std::string& library)
{
	OSinfo("loading additional library file '" + library + "'...");

	try {
		Analyser analyser(mScope);
		analyser.process(buildLibraryPath(library));

		const std::list<std::string>& libraries = analyser.getLibraryReferences();
		for ( std::list<std::string>::const_iterator it = libraries.begin(); it != libraries.end(); ++it ) {
			loadLibrary((*it));
		}

/*	Not part of this release
		InterfaceList interfaces = analyser.getInterfaces();
		for ( InterfaceList::iterator it = interfaces.begin(); it != interfaces.end(); ++it ) {
			mInterfaces.insert(std::make_pair(
				it->Typename(), (*it)
			));
		}
*/

/*	Not part of this release
		PrototypeList prototypes = analyser.getPrototypes();
		for ( PrototypeList::iterator it = prototypes.begin(); it != prototypes.end(); ++it ) {
			mRepository->addPrototype((*it));
		}
*/

		BluePrintList objects = analyser.getBluePrints();
		for ( BluePrintList::iterator it = objects.begin(); it != objects.end(); ++it ) {
			mRepository->addBlueprint((*it));
		}
	}
	catch ( std::exception& e ) {
		OSerror(e.what());
	}
}

void VirtualMachine::setBaseFolder(const std::string& base)
{
	if ( base.empty() ) {
		return;
	}

	mBaseFolder = base + "/";

	OSinfo("library root = " + mBaseFolder);
}


}
