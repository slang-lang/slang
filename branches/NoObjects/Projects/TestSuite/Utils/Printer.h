
#ifndef _Testing_Utils_Printer_h_
#define _Testing_Utils_Printer_h_


// Library includes

// Project includes
#include <Core/Interfaces/IPrinter.h>

// Forward declarations

// Namespace declarations


namespace Utils {


class Printer : public ObjectiveScript::IPrinter
{
public:
	Printer() { }

	void print(const std::string& text) {
		std::cout << text << std::endl;
	}
};


}


#endif
