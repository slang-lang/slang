
// Header
#include "TypeSystem.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/GenericObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Designtime/Exceptions.h>

// Namespace declarations
using namespace ObjectiveScript::Designtime;


namespace ObjectiveScript {


TypeSystem::TypeSystem()
{
}

TypeSystem::~TypeSystem()
{
}

void TypeSystem::define(const std::string& left, Token::Type::E operation, const std::string& right, const std::string& result)
{
	if ( !mTypeMap.contains(left) ) {
		mTypeMap.insert(left);
	}

	if ( !mTypeMap[left].contains(operation) ) {
		mTypeMap[left].insert(operation);
	}

	if ( mTypeMap[left][operation].contains(right) ) {
		throw Common::Exceptions::Exception("duplicate type system target");
	}

	mTypeMap[left][operation].insert(right);
	mTypeMap[left][operation][right] = result;
}

void TypeSystem::deinit()
{
	// nothing to do here atm
}

std::string TypeSystem::getType(const std::string& left, Token::Type::E operation, const std::string& right)
{
	if ( !mTypeMap.contains(left) ) {
//		throw Common::Exceptions::NotSupported(left);
		return "";
	}
	if ( !mTypeMap[left].contains(operation) ) {
//		throw Common::Exceptions::NotSupported(left);
		return "";
	}
	if ( !mTypeMap[left][operation].contains(right) ) {
//		throw Common::Exceptions::NotSupported(left + " with " + right);
		return "";
	}

	return mTypeMap[left][operation][right];
}

void TypeSystem::init()
{
	// bool: arithmetic
	// bool: comparison
	define(BoolObject::TYPENAME, Token::Type::COMPARE_EQUAL,   BoolObject::TYPENAME, BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::COMPARE_UNEQUAL, BoolObject::TYPENAME, BoolObject::TYPENAME);

	// double: arithmetic
	define(DoubleObject::TYPENAME, Token::Type::MATH_ADDITION, DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_DIVIDE,   DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_MULTIPLY, DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_SUBTRACT, DoubleObject::TYPENAME, DoubleObject::TYPENAME);

	// double: comparison
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_EQUAL, DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_GREATER, DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_LESS, DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL, DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_UNEQUAL, DoubleObject::TYPENAME, BoolObject::TYPENAME);

	// float: arithmetic
	define(FloatObject::TYPENAME, Token::Type::MATH_ADDITION, FloatObject::TYPENAME, FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_DIVIDE,   FloatObject::TYPENAME, FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_MULTIPLY, FloatObject::TYPENAME, FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_SUBTRACT, FloatObject::TYPENAME, FloatObject::TYPENAME);

	// float: comparison
	define(FloatObject::TYPENAME, Token::Type::COMPARE_EQUAL, FloatObject::TYPENAME, BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER, FloatObject::TYPENAME, BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, FloatObject::TYPENAME, BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS, FloatObject::TYPENAME, BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL, FloatObject::TYPENAME, BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_UNEQUAL, FloatObject::TYPENAME, BoolObject::TYPENAME);

	// int: arithmetic
	define(IntegerObject::TYPENAME, Token::Type::MATH_ADDITION, IntegerObject::TYPENAME, IntegerObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::MATH_DIVIDE,   IntegerObject::TYPENAME, IntegerObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::MATH_MODULO,   IntegerObject::TYPENAME, IntegerObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::MATH_MULTIPLY, IntegerObject::TYPENAME, IntegerObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::MATH_SUBTRACT, IntegerObject::TYPENAME, IntegerObject::TYPENAME);

	// int: comparison
	define(IntegerObject::TYPENAME, Token::Type::COMPARE_EQUAL, IntegerObject::TYPENAME, BoolObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::COMPARE_GREATER, IntegerObject::TYPENAME, BoolObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, IntegerObject::TYPENAME, BoolObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::COMPARE_LESS, IntegerObject::TYPENAME, BoolObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL, IntegerObject::TYPENAME, BoolObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::COMPARE_UNEQUAL, IntegerObject::TYPENAME, BoolObject::TYPENAME);

	// string: arithmetic
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, StringObject::TYPENAME, StringObject::TYPENAME);

	// string: comparison
	define(StringObject::TYPENAME, Token::Type::COMPARE_EQUAL, StringObject::TYPENAME, BoolObject::TYPENAME);
	//define(StringObject::TYPENAME, Token::Type::COMPARE_GREATER, StringObject::TYPENAME, BoolObject::TYPENAME);
	//define(StringObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, StringObject::TYPENAME, BoolObject::TYPENAME);
	//define(StringObject::TYPENAME, Token::Type::COMPARE_LESS, StringObject::TYPENAME, BoolObject::TYPENAME);
	//define(StringObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL, StringObject::TYPENAME, BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::COMPARE_UNEQUAL, StringObject::TYPENAME, BoolObject::TYPENAME);
}


}
