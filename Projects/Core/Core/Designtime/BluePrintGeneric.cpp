
// Header
#include "BluePrintGeneric.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrintGeneric::BluePrintGeneric()
: BluePrintSymbol(ANONYMOUS_OBJECT),
  mFilename(ANONYMOUS_OBJECT),
  mQualifiedTypename(ANONYMOUS_OBJECT),
  mTypename(ANONYMOUS_OBJECT),
  mVisibility(Visibility::Public)
{
}

BluePrintGeneric::BluePrintGeneric(const std::string& type, const std::string& filename)
: BluePrintSymbol(type),
  mFilename(filename),
  mQualifiedTypename(type),
  mTypename(type),
  mVisibility(Visibility::Public)
{
}

BluePrintGeneric::~BluePrintGeneric()
{
}

const TokenList& BluePrintGeneric::getTokens() const
{
	return mTokens;
}

Visibility::E BluePrintGeneric::getVisibility() const
{
	return mVisibility;
}

void BluePrintGeneric::setQualifiedTypename(const std::string& name)
{
	mQualifiedTypename = name;
}

void BluePrintGeneric::setTokens(const TokenList& tokens)
{
	mTokens = tokens;
}

void BluePrintGeneric::setVisibility(Visibility::E v)
{
	mVisibility = v;
}


}
}
