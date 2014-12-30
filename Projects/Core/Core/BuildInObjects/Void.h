
#ifndef Core_BuildInObjects_Void_h
#define Core_BuildInObjects_Void_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Void : public Object
{
public:
	Void()
	: Object("", "SYSTEM.OS", "Void", "")
	{ }

	Void(const std::string& value)
	: Object("", "SYSTEM.OS", "Void", value)
	{ }

public:
	void setTokens(const TokenList& tokens) {
		(void)tokens;
	}

protected:

private:

};


}


#endif
