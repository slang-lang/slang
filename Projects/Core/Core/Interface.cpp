
// Header
#include "Interface.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Interface::Interface()
: RTTI("<unknown type>", "<none>")
{
}

Interface::Interface(const std::string& type, const std::string& filename)
: RTTI(type, filename)
{
}

Interface::~Interface()
{
}

const TokenList& Interface::getTokens() const
{
	return mTokens;
}

void Interface::setTokens(const TokenList& tokens)
{
	mTokens = tokens;
}


}
