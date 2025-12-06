
#ifndef Slang_slang_app_Application_Application_h
#define Slang_slang_app_Application_Application_h


// Library includes

// Project includes
#include <Core/VirtualMachine/VirtualMachine.h>
#include "Settings.h"

// Forward declarations
namespace Slang {
	class Script;
}

// Namespace declarations


namespace Slang {


class Application
{
public:
	Application();
	~Application();

public:
	void init( int argc, const char* argv[] );
	int exec();

private:
	static void printUsage();
	static void printVersion();

	void deinit();
	void loadConfig();
    void loadServices();
	void processParameters( int argc, const char* argv[] );

private:
	Script* mScript;
    Settings mSettings;
    VirtualMachine mVirtualMachine;
};


}


#endif
