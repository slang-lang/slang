
#ifndef ObjectiveScript_Core_VirtualMachine_h
#define ObjectiveScript_Core_VirtualMachine_h


// Library include
#include <map>
#include <iostream>
#include <string>

// Project includes
#include <Core/Designtime/BluePrintObject.h>
#include <Core/Extensions/AExtension.h>
#include "Parameter.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IPrinter;
class MethodScope;
class Repository;
namespace Runtime {
	class Object;
}
class Script;

class VirtualMachine
{
public:
	VirtualMachine();
	~VirtualMachine();

public:	// Setup
	void addExtension(Extensions::AExtension *extension);
	void setBaseFolder(const std::string& base);
	void setLibraryFolder(const std::string& library);

public:
	Script* createScriptFromFile(const std::string& filename, const ParameterList& params = ParameterList());
	Script* createScriptFromString(const std::string& content, const ParameterList& params = ParameterList());

private:
	typedef std::set<std::string> ImportedLibraries;
	typedef std::set<Script*> ScriptCollection;

private:
	std::string buildPath(const std::string& basefolder, const std::string& library) const;

	Script* createScript(const std::string& content, const ParameterList& params);
	void init();
	bool loadExtensions();
	bool loadLibrary(const std::string& library);

private:
	std::string mBaseFolder;
	Extensions::ExtensionList mExtensions;
	ImportedLibraries mImportedLibraries;
	std::string mLibraryFolder;
	Repository *mRepository;
	std::string mScriptFile;
	ScriptCollection mScripts;
};


}


#endif
