
// Header
#include "BluePrint.h"

// Library includes
#include <cassert>

// Project includes
#include "Consts.h"
#include "Object.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrint::BluePrint()
: MethodScope(ANONYMOUS_OBJECT, 0),
  BluePrintSymbol(ANONYMOUS_OBJECT),
  RTTI(ANONYMOUS_OBJECT, ANONYMOUS_OBJECT),
  mName(ANONYMOUS_OBJECT),
  mVisibility(Visibility::Public)
{
}

BluePrint::BluePrint(const std::string& type, const std::string& filename, const std::string& name)
: MethodScope(type, 0),
  BluePrintSymbol(type),
  RTTI(type, filename),
  mName(name),
  mVisibility(Visibility::Public)
{
}

BluePrint::~BluePrint()
{
}

const std::string& BluePrint::getName() const
{
	return mName;
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
