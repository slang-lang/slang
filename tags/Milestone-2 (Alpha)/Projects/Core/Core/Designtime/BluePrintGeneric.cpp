
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
  mTypename(ANONYMOUS_OBJECT)
{
}

BluePrintGeneric::BluePrintGeneric(const std::string& type, const std::string& filename)
: BluePrintSymbol(type),
  mFilename(filename),
  mQualifiedTypename(type),
  mTypename(type)
{
}

BluePrintGeneric::~BluePrintGeneric()
{
}

void BluePrintGeneric::cleanup()
{
	// nothing to do here
}

const TokenList& BluePrintGeneric::getTokens() const
{
	return mTokens;
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