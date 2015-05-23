
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
	std::cout << "Usage: oscript [options] [-f] <file>" << std::endl;
	std::cout << std::endl;
	std::cout << "-f <file>      Parse and execute <file>" << std::endl;
	std::cout << "-h | --help    This help" << std::endl;
	std::cout << "-r | --root    Library root path" << std::endl;
	std::cout << "-v             Verbose output" << std::endl;
	std::cout << std::endl;
}

int main(int argc, const char* argv[])
{
#ifdef _WIN32
	// Memory leak detection
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// Memory leak detection
#endif

	Utils::Common::StdOutLogger mLogger;

	std::string filename;
	std::string root;

	if ( argc > 1 ) {
		for (int i = 1; i < argc; i++) {
			if ( Utils::Tools::StringCompare(argv[i], "-f") ) {
				filename = argv[++i];
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-h") || Utils::Tools::StringCompare(argv[i], "--help") ) {
				printUsage();
				return 0;
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-root") ) {
				if ( argc <= ++i ) {
					std::cout << "invalid number of parameters provided!" << std::endl;
					return -1;
				}
				root = argv[i];
			}
			else if ( Utils::Tools::StringCompare(argv[i], "-v") ) {
				mLogger.setLoudness(Utils::Common::ILogger::LoudnessInfo);
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

	Printer mPrinter(&mLogger);

	ObjectiveScript::VirtualMachine mVirtualMachine;
	mVirtualMachine.connectPrinter(&mPrinter);
	mVirtualMachine.setBaseFolder(root);

	try {
		mVirtualMachine.create(filename);
		// our script automatically executes it's Main object constructor,
		// so there is no need to execute a method explicit
	}
	catch ( std::exception &e ) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
