
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
	: Common::Logger(p, "")
	{ }

	void log(const std::string& text) {
		std::cout << text << std::endl;
	}
	void print(const std::string& text) {
		std::cout << text << std::endl;
	}
};


}


#endif
