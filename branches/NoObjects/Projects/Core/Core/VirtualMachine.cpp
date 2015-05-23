
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
: mBaseFolder(""),
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

	for ( ScriptCollection::iterator it = mScripts.begin(); it != mScripts.end(); ++it ) {
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

	result = mBaseFolder + result + ".os";
	return result;
}

Script* VirtualMachine::create(const std::string& filename, const ParameterList& params)
{
	init();

	OSinfo("Processing script '" + filename + "'...");

	if ( filename.empty() ) {
		OSwarn("Invalid filename '" + filename + "' provided!");
		return 0;
	}

	Script *script = new Script();
	script->connectPrinter(mPrinter);

	Analyser analyser;
	analyser.process(filename);

	StringList libraries = analyser.getLibraryReferences();
	InterfaceList interfaces = analyser.getInterfaces();
	BluePrintList objects = analyser.getBluePrints();
	PrototypeList prototypes = analyser.getPrototypes();

	for ( StringList::const_iterator it = libraries.begin(); it != libraries.end(); ++it ) {
		loadLibrary((*it));
	}

	for ( InterfaceList::iterator it = interfaces.begin(); it != interfaces.end(); ++it ) {
		mInterfaces.insert(std::make_pair(
			it->Typename(), (*it)
		));
	}

	for ( PrototypeList::iterator it = prototypes.begin(); it != prototypes.end(); ++it ) {
		mRepository->addPrototype((*it));
	}

	for ( BluePrintList::iterator it = objects.begin(); it != objects.end(); ++it ) {
		mRepository->addBlueprint((*it));

		if ( it->Filename() == filename && it->Typename() == "Main" ) {
			mObjects.insert(std::make_pair(
				it->Typename(), mRepository->createInstance(it->Typename(), "main")
			));

			ObjectCollection::iterator objIt = mObjects.find(it->Typename());
			assert(objIt != mObjects.end());

			script->assign(objIt->second);
		}
	}

	script->connectMemory(mMemory);
	script->connectRepository(mRepository);
	script->construct(params);

	mScripts.insert(script);

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
	OSinfo("Loading additional library file '" + library + "'...");

	try {
		Analyser a;
		a.process(buildLibraryPath(library));

		const std::list<std::string>& libraries = a.getLibraryReferences();
		BluePrintList objects = a.getBluePrints();
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
	if ( base.empty() ) {
		return;
	}

	mBaseFolder = base;

	OSinfo("Library root = " + mBaseFolder);
}

void VirtualMachine::setPrinter(IPrinter *p)
{
	mPrinter = p;
}


}
