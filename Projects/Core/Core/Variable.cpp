
// Header
#include "Variable.h"

// Library includes

// Project includes
#include "Exceptions.h"

// Namespace declarations


namespace ObjectiveScript {


Variable::Variable()
: mConst(false),
  mRealType(BaseType::Void),
  mStatic(false),
  mVisibility(Visibility::Private)
{
}

Variable::Variable(const std::string& name, BaseType::E type)
: mConst(false),
  mName(name),
  mRealType(type),
  mStatic(false),
  mType(BaseType::convert(type)),
  mVisibility(Visibility::Private)
{
}

Variable::Variable(const std::string& name, const std::string& type)
: mConst(false),
  mName(name),
  mRealType(BaseType::convert(type)),
  mStatic(false),
  mType(type),
  mVisibility(Visibility::Private)
{
}

Variable::Variable(const std::string& name, const std::string& type, const std::string& value)
: mConst(false),
  mName(name),
  mRealType(BaseType::Void),
  mStatic(false),
  mType(type),
  mValue(value),
  mVisibility(Visibility::Private)
{
}

Variable::~Variable()
{
}

bool Variable::isConst() const
{
	return mConst;
}

bool Variable::isStatic() const
{
	return mStatic;
}

const std::string& Variable::name() const
{
	return mName;
}

Variable::BaseType::E Variable::realType() const
{
	return mRealType;
}

void Variable::setConst(bool state)
{
	mConst = state;
}

void Variable::setStatic(bool state)
{
	mStatic = state;
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

Visibility::E Variable::visibility() const
{
	return mVisibility;
}

void Variable::visibility(const std::string& v)
{
	mVisibility = Visibility::convert(v);
}

void Variable::visibility(Visibility::E v)
{
	mVisibility = v;
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
