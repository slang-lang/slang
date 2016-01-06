
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

void BluePrint::addInterface(const Ancestor& iface)
{
	mInterfaces.insert(std::make_pair(
		iface.name(),
		iface
	));
}

const BluePrint::Ancestors& BluePrint::getAncestors() const
{
	return mAncestors;
}

const BluePrint::Ancestors& BluePrint::getInterfaces() const
{
	return mInterfaces;
}

const TokenList& BluePrint::getTokens() const
{
	return mTokens;
}

Visibility::E BluePrint::getVisibility() const
{
	return mVisibility;
}

void BluePrint::setAncestors(const Ancestors& ancestors)
{
	mAncestors = ancestors;
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
