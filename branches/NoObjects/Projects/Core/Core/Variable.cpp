
// Header
#include "Variable.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {


Variable::Variable()
{
}

Variable::Variable(const std::string& name, const std::string& type)
: mVarName(name),
  mVarType(type)
{
}

Variable::Variable(const std::string& name, const std::string& type, const std::string& value)
: mVarName(name),
  mVarType(type),
  mVarValue(value)
{
}

Variable::~Variable()
{
}

const std::string& Variable::name() const
{
	return mVarName;
}

const std::string& Variable::type() const
{
	return mVarType;
}

const std::string& Variable::value() const
{
	return mVarValue;
}

void Variable::value(const std::string& value)
{
	mVarValue = value;
}


}
