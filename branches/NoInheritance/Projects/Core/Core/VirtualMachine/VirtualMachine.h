
#ifndef ObjectiveScript_Core_VirtualMachine_VirtualMachine_h
#define ObjectiveScript_Core_VirtualMachine_VirtualMachine_h


// Library include
#include <map>
#include <iostream>
#include <string>

// Project includes
#include <Core/Designtime/BluePrintObject.h>
#include <Core/Extensions/AExtension.h>
#include <Core/Parameter.h>
#include <Core/Types.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Runtime {
	class Object;
}
class Script;

class VirtualMachine
{
public:
	class Settings {
	public:
		Settings()
		: DoSyntaxCheck(false)
		{ }

		bool DoSyntaxCheck;
	};

public:
	VirtualMachine();
	~VirtualMachine();

public:	// Setup
	void addExtension(Extensions::AExtension *extension);
	void addLibraryFolder(const std::string &library);
	Settings& settings();

public:
	Script* createScriptFromFile(const std::string& filename, const ParameterList& params = ParameterList(), Runtime::Object* result = 0);
	Script* createScriptFromString(const std::string& content, const ParameterList& params = ParameterList(), Runtime::Object* result = 0);

private:
	typedef std::set<Script*> ScriptCollection;

private:
	std::string buildPath(const std::string& basefolder, const std::string& library) const;

	Script* createScript(const std::string& content, const ParameterList& params, Runtime::Object* result);
	void init();
	bool loadExtensions();
	bool loadLibrary(const std::string& library);
	void printLibraryFolders();

private:
	Extensions::ExtensionList mExtensions;
	StringSet mImportedLibraries;
	StringSet mLibraryFolders;
	std::string mScriptFile;
	ScriptCollection mScripts;
	Settings mSettings;
};


}


#endif
