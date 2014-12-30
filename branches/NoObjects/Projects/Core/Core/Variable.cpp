
// Header
#include "Variable.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {


Variable::Variable()
: mRealType(BaseType::Void)
{
}

Variable::Variable(const std::string& name, BaseType::E type)
: mName(name),
  mRealType(type),
  mType(BaseType::convert(type))
{
}

Variable::Variable(const std::string& name, const std::string& type)
: mName(name),
  mRealType(BaseType::convert(type)),
  mType(type)
{
}

Variable::Variable(const std::string& name, const std::string& type, const std::string& value)
: mName(name),
  mRealType(BaseType::Void),
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

Variable::BaseType::E Variable::realType() const
{
	return mRealType;
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
