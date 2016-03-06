
#ifndef ObjectiveScript_VirtualMachine_h
#define ObjectiveScript_VirtualMachine_h


// Library include
#include <map>
#include <iostream>
#include <string>

// Project includes
#include "Object.h"
#include "Parameter.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IPrinter;
class IScope;
class Repository;
class Script;

class VirtualMachine
{
public:
	VirtualMachine();
	~VirtualMachine();

public:	// Setup
	void setBaseFolder(const std::string& base);

public:
	Script* createScriptFromFile(const std::string& filename, const ParameterList& params = ParameterList());
	Script* createScriptFromString(const std::string& content, const ParameterList& params = ParameterList());

protected:

private:
	typedef std::map<std::string, Designtime::BluePrint> BluePrintCollection;
	typedef std::map<std::string, Runtime::Object*> ObjectCollection;
	typedef std::set<Script*> ScriptCollection;

private:
	std::string buildLibraryPath(const std::string& library) const;
	Script* createScript(const std::string& content, const ParameterList& params);
	void init();
	void loadLibrary(const std::string& library);

private:
	std::string mBaseFolder;
	BluePrintCollection mBluePrints;
	ObjectCollection mObjects;
	Repository *mRepository;
	IScope *mScope;
	std::string mScriptFile;
	ScriptCollection mScripts;
};


}


#endif
