
#ifndef Slang_Core_Core_VirtualMachine_VirtualMachine_h
#define Slang_Core_Core_VirtualMachine_VirtualMachine_h


// Library include
#include <map>
#include <iostream>
#include <string>

// Project includes
#include <Core/Designtime/BluePrintObject.h>
#include <Core/Extensions/AExtension.h>
#ifdef _WIN32
	// Extension loading is not supported under Windows
#else
#	include <Core/Extensions/ExtensionManager.h>
#endif
#include <Core/Parameter.h>
#include <Core/Types.h>

// Forward declarations

// Namespace declarations


namespace Slang {

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
		: DoCollectErrors(false),
		  DoSanityCheck(true),
		  DoSkipExtensions(false),
		  DoSyntaxCheck(false)
		{ }

		bool DoCollectErrors;
		bool DoSanityCheck;
		bool DoSkipExtensions;
		bool DoSyntaxCheck;
	};

public:
	VirtualMachine();
	~VirtualMachine();

public:	// Setup
	void addExtension(Extensions::AExtension* extension, const std::string& library = "<internal library>");
	void addLibraryFolder(const std::string& library);
	void init();
	void printExtensions();
	void printLibraryFolders();
	Settings& settings();

public:
	Script* createScriptFromFile(const std::string& filename);
	Script* createScriptFromString(const std::string& content);

	void run(Script* script, const ParameterList& params = ParameterList(), Runtime::Object* result = nullptr);
	void runScriptFromFile(const std::string& filename, const ParameterList& params = ParameterList(), Runtime::Object* result = nullptr);
	void runScriptFromString(const std::string& content, const ParameterList& params = ParameterList(), Runtime::Object* result = nullptr);

private:
	typedef std::set<Script*> ScriptCollection;

private:
	Script* createScript(const std::string& content);
	bool loadExtension( const std::string& extension, const std::string& folder );
	bool loadExtensions();
	bool loadLibrary(const std::string& library);

private:
#ifdef _WIN32
	// Extension loading is not supported under Windows
#else
	Extensions::ExtensionManager mExtensionManager;
#endif
	Extensions::ExtensionCollection mExtensions;
	StringSet mImportedLibraries;
	bool mIsInitialized;
	OrderedStringSet mLibraryFolders;
	std::string mScriptFile;
	ScriptCollection mScripts;
	Settings mSettings;
};


}


#endif
