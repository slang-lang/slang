
#ifndef Slang_slang_app_Application_Application_h
#define Slang_slang_app_Application_Application_h


// Library includes

// Project includes
#include "Settings.h"

// Forward declarations
namespace Slang {
    class VirtualMachine;
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
    //Settings mSettings;
    VirtualMachine* mVirtualMachine;
};


}


#endif
