
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
	Printer(const Common::Logger *p)
	: Common::Logger(p, ""),
	  mActivateLogger(true),
	  mActivatePrinter(true),
	  mPrintFileAndLine(true)
	{ }

	void log(const std::string& text) {
		if ( mActivateLogger ) {
			std::cout << text << std::endl;
		}
	}
	void print(const std::string& text, const std::string& file = "", int line = 0) {
		if ( mActivatePrinter ) {
			std::cout << text;
			if ( mPrintFileAndLine ) {
				std::cout << "   [" << file << ":" << line << "]";
			}
			std::cout << std::endl;
		}
	}

private:
	bool mActivateLogger;
	bool mActivatePrinter;
	bool mPrintFileAndLine;
};


}


#endif
