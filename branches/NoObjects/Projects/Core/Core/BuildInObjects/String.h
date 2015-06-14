
#ifndef Core_BuildInObjects_String_h
#define Core_BuildInObjects_String_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class String : public Object
{
public:
	String(const std::string& value = "")
	: Object("", "SYSTEM.OS", "String", value)
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
