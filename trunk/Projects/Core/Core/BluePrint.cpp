
// Header
#include "BluePrint.h"

// Library includes

// Project includes
#include "Consts.h"

// Namespace declarations


namespace ObjectiveScript {
namespace DesignTime {


BluePrint::BluePrint()
: RTTI(ANONYMOUS_OBJECT, ANONYMOUS_OBJECT),
  mVisibility(Visibility::Public)
{
}

BluePrint::BluePrint(const std::string& type, const std::string& filename)
: RTTI(type, filename),
  mVisibility(Visibility::Public)
{
}

BluePrint::~BluePrint()
{
}

const TokenList& BluePrint::getTokens() const
{
	return mTokens;
}

Visibility::E BluePrint::getVisibility() const
{
	return mVisibility;
}

void BluePrint::setTokens(const TokenList& tokens)
{
	mTokens = tokens;
}

void BluePrint::setVisibility(Visibility::E v)
{
	mVisibility = v;
}


}
}
