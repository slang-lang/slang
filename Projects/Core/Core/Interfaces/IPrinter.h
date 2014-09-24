
#ifndef ObjectiveScript_Interfaces_IPrinter_h
#define ObjectiveScript_Interfaces_IPrinter_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class IPrinter
{
public:
	virtual ~IPrinter() { }

	virtual void print(const std::string& text) = 0;
};


}


#endif
