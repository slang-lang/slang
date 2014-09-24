
#ifdef _WIN32
	// Memory leak check - Begin
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>

	#include <iostream>
	#include <crtdbg.h>
	#ifdef _DEBUG
	#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define new DEBUG_NEW
	#endif
	// Memory leak check - End
#endif

// Library includes

// Project includes
#include <Common/StdOutLogger.h>
#include <Core/Interfaces/IPrinter.h>
#include <Core/VirtualMachine.h>
#include <Tools/Strings.h>

// Namespace declarations


class Printer : public ObjectiveScript::IPrinter
{
public:
	Printer(Utils::Common::Logger *l)
	: mLogger(l)
	{ }

public:
	void print(const std::string& text) {
		std::cout << text << std::endl;
	}

private:
	Utils::Common::Logger *mLogger;
};


int main(int argc, const char* argv[])
{
#ifdef _WIN32
	// Memory leak detection
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// Memory leak detection
#endif

	Utils::Common::Logger *logger = new Utils::Common::StdOutLogger();	//0;

/*
	if ( argc > 1 ) {
		for (int i = 1; i < argc; i++) {
			char buf[255];
			sprintf_s(buf, "%s", argv[i]);

			if ( Utils::Tools::StringCompare(buf, "-v") ) {
				logger = new Utils::Common::StdOutLogger();
			}
		}
	}
*/

	if ( !logger ) {
		logger = new Utils::Common::Logger("objectivescript.log");
	}

	try {
		Printer mPrinter(logger);

		ObjectiveScript::VirtualMachine *mVirtualMachine = new ObjectiveScript::VirtualMachine();
		mVirtualMachine->connectPrinter(&mPrinter);
		mVirtualMachine->setBaseFolder("");
	}
	catch ( std::exception &e ) {
		std::cout << "Unhandled std::exception: " << e.what();
		logger->LogError("Unhandled std::exception: " + std::string(e.what()), __FILE__, __LINE__);
	}

	delete logger;
}