
#ifndef _Testing_Utils_Printer_h_
#define _Testing_Utils_Printer_h_


// Library includes

// Project includes
#include <Core/Interfaces/IPrinter.h>
#include <Common/Logger.h>

// Forward declarations

// Namespace declarations


namespace Utils {


class Printer : public ObjectiveScript::IPrinter,
				public Common::Logger
{
public:
	Printer(const Common::ILogger *p)
	: Common::Logger(p, ""),
	  mActivateLogger(true),
	  mActivatePrinter(true),
	  mPrintFileAndLine(false)
	{ }

	void activateLogger(bool state) {
		mActivateLogger = state;
	}

	void activatePrinter(bool state) {
		mActivatePrinter = state;
	}

	void printFileAndLine(bool state) {
		mPrintFileAndLine = state;
	}

public:
	void log(const std::string& text) {
		if ( mActivateLogger ) {
			LogInfo(text, "", 0);
		}
	}
	void print(const std::string& text, const std::string& file = "", int line = 0) {
		if ( mActivatePrinter ) {
			std::cout << text;
			if ( mPrintFileAndLine ) {
				std::cout << "   [" << file << ":" << line << "]";
				std::cout << std::endl;
			}
		}
	}

private:
	bool mActivateLogger;
	bool mActivatePrinter;
	bool mPrintFileAndLine;
};


}


#endif
