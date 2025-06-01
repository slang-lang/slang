
#ifndef Slang_slang_pkg_Application_Application_h
#define Slang_slang_pkg_Application_Application_h


// Library includes

// Project includes
#include <Types.h>
#include "Settings.h"

// Forward declarations

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
	static void printUsage( const StringList& params );
	static void printVersion();

	void deinit();
	void processParameters( int argc, const char* argv[] );

private:
    //Settings mSettings;
};


}


#endif
