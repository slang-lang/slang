
// Header
#include "BluePrintGeneric.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrintGeneric::BluePrintGeneric()
: mFilename(ANONYMOUS_OBJECT),
  mParent(0),
  mQualifiedTypename(ANONYMOUS_OBJECT),
  mTypename(ANONYMOUS_OBJECT)
{
}

BluePrintGeneric::BluePrintGeneric(const std::string& type, const std::string& filename)
: mFilename(filename),
  mParent(0),
  mQualifiedTypename(type),
  mTypename(type)
{
}

BluePrintGeneric::~BluePrintGeneric()
{
}

IScope* BluePrintGeneric::getParent() const
{
	return mParent;
}

const TokenList& BluePrintGeneric::getTokens() const
{
	return mTokens;
}

void BluePrintGeneric::setParent(IScope* parent)
{
	mParent = parent;
}

void BluePrintGeneric::setQualifiedTypename(const std::string& name)
{
	mQualifiedTypename = name;
}

void BluePrintGeneric::setTokens(const TokenList& tokens)
{
	mTokens = tokens;
}


}
}
