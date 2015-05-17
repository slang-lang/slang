
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
