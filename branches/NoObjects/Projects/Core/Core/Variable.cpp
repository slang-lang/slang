
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
: mName(name),
  mType(type)
{
}

Variable::Variable(const std::string& name, const std::string& type, const std::string& value)
: mName(name),
  mType(type),
  mValue(value)
{
}

Variable::~Variable()
{
}

const std::string& Variable::name() const
{
	return mName;
}

const std::string& Variable::type() const
{
	return mType;
}

const std::string& Variable::value() const
{
	return mValue;
}

void Variable::value(const std::string& value)
{
	if ( isConst() ) {
		throw Exception("tried to change const object");
	}

	mValue = value;
}

bool Variable::operator==(const Variable& other)
{
	return (this->value() == other.value());
}

bool Variable::operator()()
{
	return (this->value() != "0");
}



}
