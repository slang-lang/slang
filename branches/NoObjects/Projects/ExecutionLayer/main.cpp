
// Library includes

// Project includes
#include <Common/StdOutLogger.h>
#include <Core/Interfaces/IPrinter.h>
#include <Core/Script.h>
#include <Core/Types.h>
#include <Core/VirtualMachine.h>
#include <Tools/Strings.h>

// Namespace declarations

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

	#include <vld.h>
#endif


class Printer : public ObjectiveScript::IPrinter
{
public:
	Printer(Utils::Common::ILogger *l)
	: mLogger(l)
	{ }

public:
	void log(const std::string& text) {
		mLogger->LogDebug(text, 0, 0);
	}

	void print(const std::string& text) {
		std::cout << text << std::endl;
	}

private:
	Utils::Common::ILogger *mLogger;
};

void printUsage()
{
	printf("usage:\n");
	printf("\n");
	printf("-v\t\t\tverbose output\n");
	printf("-h|--help\t\tthis text\n");
	printf("\n");
}

int main(int argc, const char* argv[])
{
#ifdef _WIN32
	// Memory leak detection
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// Memory leak detection
#endif

	Utils::Common::ILogger *logger = new Utils::Common::StdOutLogger();

	std::string filename;
	ObjectiveScript::VariablesList params;

	if ( argc > 1 ) {
		for (int i = 1; i < argc; i++) {
			if ( Utils::Tools::StringCompare(argv[i], "-v") ) {
				logger->setLoudness(Utils::Common::ILogger::LoudnessInfo);
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-h") || Utils::Tools::StringCompare(argv[i], "--help") ) {
				printUsage();
			}
			else {
				filename = argv[i];
			}
		}
	}
	
	if ( filename.empty() ) {
		printUsage();

		return 0;
	}

	Printer mPrinter(logger);

	ObjectiveScript::VirtualMachine mVirtualMachine;
	mVirtualMachine.connectPrinter(&mPrinter);
	//mVirtualMachine.setBaseFolder("./");

	try {
		mVirtualMachine.create(filename);
		// our script automatically executes it's Main object's constructor,
		// so there is no need to execute a method explicit
	}
	catch ( std::exception &e ) {
		std::cout << e.what() << std::endl;
	}

	delete logger;

	return 0;
}
