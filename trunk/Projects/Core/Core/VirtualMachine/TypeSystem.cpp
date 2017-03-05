
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
		throw Common::Exceptions::NotSupported(left);
//		return "";
	}
	if ( !mTypeMap[left].contains(operation) ) {
		throw Common::Exceptions::NotSupported(left);
//		return "";
	}
	if ( !mTypeMap[left][operation].contains(right) ) {
		throw Common::Exceptions::NotSupported(left + " with " + right);
//		return "";
	}

	return mTypeMap[left][operation][right];
}

void TypeSystem::init()
{
	initBool();
	initDouble();
	initFloat();
	initInt();
	initObject();
	initString();
}

void TypeSystem::initBool()
{
	// assign
	define(BoolObject::TYPENAME, Token::Type::ASSIGN, BoolObject::TYPENAME, BoolObject::TYPENAME);

	// arithmetic

	// comparison
	define(BoolObject::TYPENAME, Token::Type::COMPARE_EQUAL,   BoolObject::TYPENAME, BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::COMPARE_UNEQUAL, BoolObject::TYPENAME, BoolObject::TYPENAME);

	// typecasts
	define(BoolObject::TYPENAME, Token::Type::TYPECAST, DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::TYPECAST, FloatObject::TYPENAME, FloatObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::TYPECAST, IntegerObject::TYPENAME, IntegerObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::TYPECAST, StringObject::TYPENAME, StringObject::TYPENAME);
}

void TypeSystem::initDouble()
{
	// assign
	define(DoubleObject::TYPENAME, Token::Type::ASSIGN, DoubleObject::TYPENAME, DoubleObject::TYPENAME);

	// arithmetic
	define(DoubleObject::TYPENAME, Token::Type::MATH_ADDITION, DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_ADDITION, FloatObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_ADDITION, IntegerObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_DIVIDE,   DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_DIVIDE,   FloatObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_DIVIDE,   IntegerObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_MULTIPLY, DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_MULTIPLY, FloatObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_MULTIPLY, IntegerObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_SUBTRACT, DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_SUBTRACT, FloatObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_SUBTRACT, IntegerObject::TYPENAME, DoubleObject::TYPENAME);

	// comparison
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_EQUAL, DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_GREATER, DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_LESS, DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL, DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_UNEQUAL, DoubleObject::TYPENAME, BoolObject::TYPENAME);

	// typecasts
	define(DoubleObject::TYPENAME, Token::Type::TYPECAST, BoolObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::TYPECAST, FloatObject::TYPENAME, FloatObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::TYPECAST, IntegerObject::TYPENAME, IntegerObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::TYPECAST, StringObject::TYPENAME, StringObject::TYPENAME);
}

void TypeSystem::initFloat()
{
	// assign
	define(FloatObject::TYPENAME, Token::Type::ASSIGN, FloatObject::TYPENAME, FloatObject::TYPENAME);

	// arithmetic
	define(FloatObject::TYPENAME, Token::Type::MATH_ADDITION, DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_ADDITION, FloatObject::TYPENAME, FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_ADDITION, IntegerObject::TYPENAME, FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_DIVIDE,   FloatObject::TYPENAME, FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_MULTIPLY, FloatObject::TYPENAME, FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_SUBTRACT, FloatObject::TYPENAME, FloatObject::TYPENAME);

	// comparison
	define(FloatObject::TYPENAME, Token::Type::COMPARE_EQUAL, FloatObject::TYPENAME, BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER, FloatObject::TYPENAME, BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, FloatObject::TYPENAME, BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS, FloatObject::TYPENAME, BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL, FloatObject::TYPENAME, BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_UNEQUAL, FloatObject::TYPENAME, BoolObject::TYPENAME);

	// typecasts
	define(FloatObject::TYPENAME, Token::Type::TYPECAST, BoolObject::TYPENAME, BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::TYPECAST, DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::TYPECAST, IntegerObject::TYPENAME, IntegerObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::TYPECAST, StringObject::TYPENAME, StringObject::TYPENAME);
}

void TypeSystem::initInt()
{
	// assign
	define(IntegerObject::TYPENAME, Token::Type::ASSIGN, IntegerObject::TYPENAME, IntegerObject::TYPENAME);

	// arithmetic
	define(IntegerObject::TYPENAME, Token::Type::MATH_ADDITION, DoubleObject::TYPENAME,  DoubleObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::MATH_ADDITION, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::MATH_ADDITION, IntegerObject::TYPENAME, IntegerObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::MATH_DIVIDE,   IntegerObject::TYPENAME, IntegerObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::MATH_MODULO,   IntegerObject::TYPENAME, IntegerObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::MATH_MULTIPLY, IntegerObject::TYPENAME, IntegerObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::MATH_SUBTRACT, IntegerObject::TYPENAME, IntegerObject::TYPENAME);

	// comparison
	define(IntegerObject::TYPENAME, Token::Type::COMPARE_EQUAL, IntegerObject::TYPENAME, BoolObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::COMPARE_GREATER, IntegerObject::TYPENAME, BoolObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, IntegerObject::TYPENAME, BoolObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::COMPARE_LESS, IntegerObject::TYPENAME, BoolObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL, IntegerObject::TYPENAME, BoolObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::COMPARE_UNEQUAL, IntegerObject::TYPENAME, BoolObject::TYPENAME);

	// typecasts
	define(IntegerObject::TYPENAME, Token::Type::TYPECAST, BoolObject::TYPENAME, BoolObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::TYPECAST, DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::TYPECAST, FloatObject::TYPENAME, FloatObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::TYPECAST, StringObject::TYPENAME, StringObject::TYPENAME);
}

void TypeSystem::initObject()
{
	// assign
	define(GenericObject::TYPENAME, Token::Type::ASSIGN, GenericObject::TYPENAME, GenericObject::TYPENAME);

	// arithmetic

	// comparison
	define(GenericObject::TYPENAME, Token::Type::COMPARE_EQUAL,   GenericObject::TYPENAME, GenericObject::TYPENAME);
	define(GenericObject::TYPENAME, Token::Type::COMPARE_UNEQUAL, GenericObject::TYPENAME, GenericObject::TYPENAME);

	// typecasts
}

void TypeSystem::initString()
{
	// assign
	define(StringObject::TYPENAME, Token::Type::ASSIGN, StringObject::TYPENAME, StringObject::TYPENAME);

	// arithmetic
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, BoolObject::TYPENAME, StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, DoubleObject::TYPENAME, StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, FloatObject::TYPENAME, StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, IntegerObject::TYPENAME, StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, StringObject::TYPENAME, StringObject::TYPENAME);

	// comparison
	define(StringObject::TYPENAME, Token::Type::COMPARE_EQUAL, StringObject::TYPENAME, BoolObject::TYPENAME);
	//define(StringObject::TYPENAME, Token::Type::COMPARE_GREATER, StringObject::TYPENAME, BoolObject::TYPENAME);
	//define(StringObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, StringObject::TYPENAME, BoolObject::TYPENAME);
	//define(StringObject::TYPENAME, Token::Type::COMPARE_LESS, StringObject::TYPENAME, BoolObject::TYPENAME);
	//define(StringObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL, StringObject::TYPENAME, BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::COMPARE_UNEQUAL, StringObject::TYPENAME, BoolObject::TYPENAME);

	// typecasts
	//define(StringObject::TYPENAME, Token::Type::TYPECAST, BoolObject::TYPENAME, BoolObject::TYPENAME);
	//define(StringObject::TYPENAME, Token::Type::TYPECAST, DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	//define(StringObject::TYPENAME, Token::Type::TYPECAST, FloatObject::TYPENAME, FloatObject::TYPENAME);
	//define(StringObject::TYPENAME, Token::Type::TYPECAST, IntegerObject::TYPENAME, IntegerObject::TYPENAME);
}


}
