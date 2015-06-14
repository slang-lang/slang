
#ifndef Core_BuildInObjects_Number_h
#define Core_BuildInObjects_Number_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Number : public Object
{
public:
	Number(const std::string& value = "0")
	: Object("", "SYSTEM.OS", "Number", value)
	{
		Constructor(ParameterList());
	}

public:
	void setTokens(const TokenList& /*tokens*/) { }

protected:

private:

};


}


#endif
