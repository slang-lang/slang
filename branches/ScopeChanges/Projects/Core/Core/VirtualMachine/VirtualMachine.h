
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
		: DoSanityCheck(true),
		  DoSyntaxCheck(false)
		{ }

		bool DoSanityCheck;
		bool DoSyntaxCheck;
	};

public:
	VirtualMachine();
	~VirtualMachine();

public:	// Setup
	void addExtension(Extensions::AExtension *extension);
	void addLibraryFolder(const std::string &library);
	void init();
	Settings& settings();

public:
	Script* createScriptFromFile(const std::string& filename, bool collectErrors = false);
	Script* createScriptFromString(const std::string& content, bool collectErrors = false);

	void run(Script* script, const ParameterList& params = ParameterList(), Runtime::Object* result = 0);
	void runScriptFromFile(const std::string& filename, const ParameterList& params = ParameterList(), Runtime::Object* result = 0);
	void runScriptFromString(const std::string& content, const ParameterList& params = ParameterList(), Runtime::Object* result = 0);

private:
	typedef std::set<Script*> ScriptCollection;

private:
	Script* createScript(const std::string& content, bool collectErrors = false);
	bool loadExtensions();
	bool loadLibrary(const std::string& library);
	void printLibraryFolders();

private:
	Extensions::ExtensionList mExtensions;
	StringSet mImportedLibraries;
	bool mIsInitialized;
	StringSet mLibraryFolders;
	std::string mScriptFile;
	ScriptCollection mScripts;
	Settings mSettings;
};


}


#endif