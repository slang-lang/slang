
// Header
#include "BluePrint.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


BluePrint::BluePrint()
: RTTI("<unknown type>", "<none>"),
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

const BluePrint::Ancestors& BluePrint::getAncestors() const
{
	return mAncestors;
}

void BluePrint::setAncestors(const Ancestors& ancestors)
{
	mAncestors = ancestors;
}

const TokenList& BluePrint::getTokens() const
{
	return mTokens;
}

void BluePrint::setTokens(const TokenList& tokens)
{
	mTokens = tokens;
}

Visibility::E BluePrint::getVisibility() const
{
	return mVisibility;
}

void BluePrint::setVisibility(Visibility::E v)
{
	mVisibility = v;
}


}
