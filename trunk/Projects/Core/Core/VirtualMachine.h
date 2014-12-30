
#ifndef ObjectiveScript_VirtualMachine_h
#define ObjectiveScript_VirtualMachine_h


// Library include
#include <map>
#include <iostream>
#include <string>

// Project includes
#include "Object.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IPrinter;
class Memory;
class Repository;
class Script;

class VirtualMachine
{
public:
	VirtualMachine();
	~VirtualMachine();

public:	// Setup
	void connectPrinter(IPrinter *p);
	void setBaseFolder(const std::string& base);

public:
	Script* create(const std::string& filename);

protected:

private:
	typedef std::map<std::string, BluePrint> BluePrintMap;
	typedef std::map<std::string, Object> ObjectMap;

private:
	std::string buildLibraryPath(const std::string& library) const;
	void loadLibrary(const std::string& library);

private:
	std::string		mBaseFolder;
	BluePrintMap	mBluePrints;
	size_t			mCounter;
	Memory			*mMemory;
	ObjectMap		mObjects;
	IPrinter		*mPrinter;
	Repository		*mRepository;
};


}


#endif
