
// Header
#include "Condition.h"

// Library includes

// Project includes
#include <Core/Object.h>
#include <Core/Runtime/OperatorOverloading.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Core {


Condition::Condition()
: mType(Type::Invalid)
{
}

Condition::Condition(const std::string& lhs, Type::E type, const std::string& rhs)
: mLeft(lhs),
  mRight(rhs),
  mType(type)
{
}

Condition::Condition(const std::string& lhs, const std::string& type, const std::string& rhs)
: mLeft(lhs),
  mRight(rhs)
{
	mType = ConditionFromString(type);
}

Condition::~Condition()
{
}

Condition::Type::E Condition::ConditionFromString(const std::string& type) const
{
	if ( type == "==" ) return Type::Equals;
	else if ( type == ">" ) return Type::Greater;
	else if ( type == ">=" ) return Type::GreaterEqual;
	else if ( type == "<" ) return Type::Less;
	else if ( type == "<=" ) return Type::LessEqual;
	else if ( type == "!=" ) return Type::Unequal;
	else return Type::Invalid;
}

bool Condition::evaluate(Symbol* lhs, Symbol* rhs) const
{
	if ( !lhs || !rhs ) {
		// invalid sides provided!
		return true;
	}

	Runtime::Object* left = dynamic_cast<Runtime::Object*>(lhs);
	Runtime::Object* right = dynamic_cast<Runtime::Object*>(rhs);

	switch ( mType ) {
		case Type::Equals:
			return operator_binary_equal(left, right);
		case Type::Greater:
			return operator_binary_greater(left, right);
		case Type::GreaterEqual:
			return operator_binary_greater_equal(left, right);
		case Type::Less:
			return operator_binary_less(left, right);
		case Type::LessEqual:
			return operator_binary_less_equal(left, right);
		case Type::Unequal:
			return !operator_binary_equal(left, right);
		case Type::Invalid:
			return true;
	}

	return false;
}

bool Condition::isValid() const
{
	return mType != Type::Invalid;
}

const std::string& Condition::lhs() const
{
	return mLeft;
}

const std::string& Condition::rhs() const
{
	return mRight;
}

std::string Condition::toString() const
{
	std::string result;

	result += mLeft;
	switch ( mType ) {
		case Type::Equals: result += " == "; break;
		case Type::Greater: result += " > "; break;
		case Type::GreaterEqual: result += " >= "; break;
		case Type::Less: result += " < "; break;
		case Type::LessEqual: result += " <= "; break;
		case Type::Unequal: result += " != "; break;
		case Type::Invalid: result += " "; break;
	}
	result += mRight;

	return result;
}

Condition::Type::E Condition::type() const
{
	return mType;
}



}
}
