
#ifndef Core_BuildInObjects_Bool_h
#define Core_BuildInObjects_Bool_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Bool : public Object
{
public:
	Bool(const std::string& value = "false")
	: Object("", "SYSTEM.OS", "Bool", value)
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
