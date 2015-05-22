
// Header
#include "VirtualMachine.h"

// Library includes

// Project includes
#include <Core/Interfaces/IPrinter.h>
#include <Core/Utils/Utils.h>
#include "Analyser.h"
#include "Memory.h"
#include "Preprocessor.h"
#include "Repository.h"
#include "Script.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


VirtualMachine::VirtualMachine()
: mBaseFolder("."),
  mMemory(0),
  mPrinter(0),
  mRepository(0)
{
	mMemory = new Memory();
	mRepository = new Repository(mMemory);
}

VirtualMachine::~VirtualMachine()
{
	mBluePrints.clear();
	mInterfaces.clear();
	mObjects.clear();

	for ( Scripts::iterator it = mScripts.begin(); it != mScripts.end(); ++it ) {
		delete (*it);
	}
	mScripts.clear();

	delete mMemory;
	delete mRepository;
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

	result = mBaseFolder + "/" + result + ".os";
	return result;
}

void VirtualMachine::connectPrinter(IPrinter *p)
{
	mPrinter = p;
}

Script* VirtualMachine::create(const std::string& filename)
{
	OSinfo("create('" + filename + "')");

	if ( filename.empty() ) {
		OSwarn("invalid filename '" + filename + "' provided!");
		return 0;
	}

	Script *script = new Script();
	mScripts.insert(script);

	script->connectPrinter(mPrinter);

	Analyser analyser;
	analyser.process(filename);

	std::list<std::string> libraries = analyser.getLibraryReferences();
	InterfaceList interfaces = analyser.getInterfaces();
	BluePrintList objects = analyser.getObjects();
	PrototypeList prototypes = analyser.getPrototypes();

	for ( std::list<std::string>::const_iterator it = libraries.begin(); it != libraries.end(); ++it ) {
		loadLibrary((*it));
	}

	for ( BluePrintList::iterator it = objects.begin(); it != objects.end(); ++it ) {
		mRepository->addBlueprint((*it));

		if ( it->Filename() == filename && it->Typename() == "Main" ) {
			mObjects.insert(std::make_pair(
				it->Typename(), mRepository->createInstance(it->Typename(), "main")
			));

			ObjectMap::iterator objIt = mObjects.find(it->Typename());
			assert(objIt != mObjects.end());

			script->assign(objIt->second);
		}
	}

	for ( InterfaceList::iterator it = interfaces.begin(); it != interfaces.end(); ++it ) {
		mInterfaces.insert(std::make_pair(
			it->Typename(), (*it)
		));
	}

	for ( PrototypeList::iterator it = prototypes.begin(); it != prototypes.end(); ++it ) {
		mRepository->addPrototype((*it));
	}

	script->connectMemory(mMemory);
	script->connectRepository(mRepository);
	script->construct();

	return script;
}

void VirtualMachine::loadLibrary(const std::string& library)
{
	OSinfo("Loading additional library file '" + library + "'");

	try {
		Analyser a;
		a.process(buildLibraryPath(library));

		const std::list<std::string>& libraries = a.getLibraryReferences();
		BluePrintList objects = a.getObjects();
		PrototypeList prototypes = a.getPrototypes();

		for ( std::list<std::string>::const_iterator it = libraries.begin(); it != libraries.end(); ++it ) {
			loadLibrary((*it));
		}

		for ( BluePrintList::iterator it = objects.begin(); it != objects.end(); ++it ) {
			mRepository->addBlueprint((*it));
		}

		for ( PrototypeList::iterator it = prototypes.begin(); it != prototypes.end(); ++it ) {
			mRepository->addPrototype((*it));
		}
	}
	catch ( std::exception& e ) {
		OSerror(e.what());
	}
}

void VirtualMachine::setBaseFolder(const std::string& base)
{
	mBaseFolder = base;
}


}
