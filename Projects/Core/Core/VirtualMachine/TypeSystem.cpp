
// Header
#include "TypeSystem.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/EnumerationObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/Int16Type.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/UserObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>

// Namespace declarations
using namespace Slang::Designtime;


namespace Slang {


void TypeSystem::define(const std::string& left, Token::Type::E operation, const std::string& right, const std::string& result)
{
	if ( !mTypeMap.contains(left) ) {
		mTypeMap.insert(left);
	}

	if ( !mTypeMap[left].contains(operation) ) {
		mTypeMap[left].insert(operation);
	}

	if ( mTypeMap[left][operation].contains(right) ) {
		//throw Common::Exceptions::Exception("duplicate type system target: " + left + " with " + right);
		return;
	}

	mTypeMap[left][operation].insert(right);
	mTypeMap[left][operation][right] = result;
}

bool TypeSystem::exists(const std::string& left, Token::Type::E operation, const std::string& right)
{
	if ( !mTypeMap.contains(left) ) {
		return false;
	}
	if ( !mTypeMap[left].contains(operation) ) {
		return false;
	}
	if ( !mTypeMap[left][operation].contains(right) ) {
		return false;
	}

	return !mTypeMap[left][operation][right].empty();
}

void TypeSystem::deinit()
{
	// nothing to do here atm
}

std::string TypeSystem::getType(const std::string& left, const Token& operation, const std::string& right)
{
	if ( !mTypeMap.contains(left) ) {
		throw Common::Exceptions::UnknownIdentifier("unknown type '" + left + "' detected during type check", operation.position());
	}
	if ( !mTypeMap[left].contains(operation.type()) ) {
		throw Common::Exceptions::UnknownOperation("unknown operation " + operation.content() + " detected for type '" + left + "' during type check", operation.position());
	}
	if ( !mTypeMap[left][operation.type()].contains(right) ) {
		throw Common::Exceptions::TypeMismatch(left + " " + operation.content() + " " + right, operation.position());
	}

	return mTypeMap[left][operation.type()][right];
}

void TypeSystem::init()
{
	initBool();
	initDouble();
	initEnumeration();
	initFloat();
	initInt16();
	initInt32();
	initObject();
	initString();
}

void TypeSystem::initBool()
{
	// arithmetic
	// no arithmetic operators available

	// assign
	define(BoolObject::TYPENAME, Token::Type::ASSIGN, BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::ASSIGN, DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::ASSIGN, FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::ASSIGN, StringObject::TYPENAME,  BoolObject::TYPENAME);

	// bit
	// no bitwise operators available

	// boolean
	define(BoolObject::TYPENAME, Token::Type::AND,  BoolObject::TYPENAME,   BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::AND,  DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::AND,  FloatObject::TYPENAME,  BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,    BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,    BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::AND,  StringObject::TYPENAME, BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::NAND, BoolObject::TYPENAME,   BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::NAND, DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::NAND, FloatObject::TYPENAME,  BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,    BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,    BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::NAND, StringObject::TYPENAME, BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::NOR,  BoolObject::TYPENAME,   BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::NOR,  DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::NOR,  FloatObject::TYPENAME,  BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,    BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,    BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::NOR,  StringObject::TYPENAME, BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::OR,   BoolObject::TYPENAME,   BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::OR,   DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::OR,   FloatObject::TYPENAME,  BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,    BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,    BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::OR,   StringObject::TYPENAME, BoolObject::TYPENAME);

	// comparison
	define(BoolObject::TYPENAME, Token::Type::COMPARE_EQUAL,   BoolObject::TYPENAME, BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::COMPARE_UNEQUAL, BoolObject::TYPENAME, BoolObject::TYPENAME);

	// shift
	// no shift operators available

	// typecast
	define(BoolObject::TYPENAME, Token::Type::TYPECAST, BoolObject::TYPENAME,   BoolObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::TYPECAST, DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	//define(BoolObject::TYPENAME, Token::Type::TYPECAST, EnumerationObject::TYPENAME, EnumerationObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::TYPECAST, FloatObject::TYPENAME,  FloatObject::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::TYPECAST, Int16Type::TYPENAME,    Int16Type::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,    Int32Type::TYPENAME);
	define(BoolObject::TYPENAME, Token::Type::TYPECAST, StringObject::TYPENAME, StringObject::TYPENAME);
}

void TypeSystem::initDouble()
{
	// arithmetic
	define(DoubleObject::TYPENAME, Token::Type::MATH_ADDITION, DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_ADDITION, FloatObject::TYPENAME,  DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_ADDITION, Int32Type::TYPENAME,    DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_DIVIDE,   DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_DIVIDE,   FloatObject::TYPENAME,  DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_DIVIDE,   Int32Type::TYPENAME,    DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_MULTIPLY, DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_MULTIPLY, FloatObject::TYPENAME,  DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_MULTIPLY, Int32Type::TYPENAME,    DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_SUBTRACT, DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_SUBTRACT, FloatObject::TYPENAME,  DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_SUBTRACT, Int32Type::TYPENAME,    DoubleObject::TYPENAME);

	// assign
	define(DoubleObject::TYPENAME, Token::Type::ASSIGN, BoolObject::TYPENAME,   DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::ASSIGN, DoubleObject::TYPENAME, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::ASSIGN, FloatObject::TYPENAME,  DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME,    DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME,    DoubleObject::TYPENAME);

	// bit
	// no bitwise operators available

	// boolean
	define(DoubleObject::TYPENAME, Token::Type::AND,  BoolObject::TYPENAME,   BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::AND,  DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::AND,  FloatObject::TYPENAME,  BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::AND,  StringObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::NAND, BoolObject::TYPENAME,   BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::NAND, DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::NAND, FloatObject::TYPENAME,  BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::NAND, StringObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::NOR,  BoolObject::TYPENAME,   BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::NOR,  DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::NOR,  FloatObject::TYPENAME,  BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::NOR,  StringObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::OR,   BoolObject::TYPENAME,   BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::OR,   DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::OR,   FloatObject::TYPENAME,  BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::OR,   StringObject::TYPENAME, BoolObject::TYPENAME);

	// comparison
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_EQUAL,         DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_EQUAL,         FloatObject::TYPENAME,  BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_EQUAL,         Int16Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_EQUAL,         Int32Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_GREATER,       DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_GREATER,       FloatObject::TYPENAME,  BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_GREATER,       Int16Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_GREATER,       Int32Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, FloatObject::TYPENAME,  BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int16Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int32Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_LESS,          DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_LESS,          FloatObject::TYPENAME,  BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_LESS,          Int16Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_LESS,          Int32Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    FloatObject::TYPENAME,  BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int16Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int32Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_UNEQUAL,       DoubleObject::TYPENAME, BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_UNEQUAL,       FloatObject::TYPENAME,  BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int16Type::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int32Type::TYPENAME,    BoolObject::TYPENAME);

	// shift
	// no shift operators available

	// typecast
	define(DoubleObject::TYPENAME, Token::Type::TYPECAST, BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::TYPECAST, DoubleObject::TYPENAME,  DoubleObject::TYPENAME);
	//define(DoubleObject::TYPENAME, Token::Type::TYPECAST, EnumerationObject::TYPENAME, EnumerationObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::TYPECAST, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::TYPECAST, StringObject::TYPENAME,  StringObject::TYPENAME);

	// unary
	define(DoubleObject::TYPENAME, Token::Type::MATH_ADDITION, _unary_, DoubleObject::TYPENAME);
	define(DoubleObject::TYPENAME, Token::Type::MATH_SUBTRACT, _unary_, DoubleObject::TYPENAME);
}

void TypeSystem::initEnumeration()
{
    // assign
    define(EnumerationObject::TYPENAME, Token::Type::ASSIGN, EnumerationObject::TYPENAME, EnumerationObject::TYPENAME);

    // bit
	// no bitwise operators available

    // shift
    // no shift operators available

	// typecast
	define(EnumerationObject::TYPENAME, Token::Type::TYPECAST, BoolObject::TYPENAME,        BoolObject::TYPENAME);
	define(EnumerationObject::TYPENAME, Token::Type::TYPECAST, DoubleObject::TYPENAME,      DoubleObject::TYPENAME);
	//define(EnumerationObject::TYPENAME, Token::Type::TYPECAST, EnumerationObject::TYPENAME, EnumerationObject::TYPENAME);
	define(EnumerationObject::TYPENAME, Token::Type::TYPECAST, FloatObject::TYPENAME,       FloatObject::TYPENAME);
	define(EnumerationObject::TYPENAME, Token::Type::TYPECAST, Int16Type::TYPENAME,         Int16Type::TYPENAME);
	define(EnumerationObject::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,         Int32Type::TYPENAME);
	define(EnumerationObject::TYPENAME, Token::Type::TYPECAST, StringObject::TYPENAME,      StringObject::TYPENAME);

	// unary
	// no unary operators available
}

void TypeSystem::initFloat()
{
	// assign
	define(FloatObject::TYPENAME, Token::Type::ASSIGN, BoolObject::TYPENAME,    FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::ASSIGN, DoubleObject::TYPENAME,  FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::ASSIGN, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME,     FloatObject::TYPENAME);

	// arithmetic
	define(FloatObject::TYPENAME, Token::Type::MATH_ADDITION, DoubleObject::TYPENAME,  FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_ADDITION, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_ADDITION, Int16Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_ADDITION, Int32Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_DIVIDE,   DoubleObject::TYPENAME,  FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_DIVIDE,   FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_DIVIDE,   Int16Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_DIVIDE,   Int32Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_MULTIPLY, DoubleObject::TYPENAME,  FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_MULTIPLY, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_MULTIPLY, Int16Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_MULTIPLY, Int32Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_SUBTRACT, DoubleObject::TYPENAME,  FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_SUBTRACT, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_SUBTRACT, Int16Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_SUBTRACT, Int32Type::TYPENAME,     FloatObject::TYPENAME);

	// bit
	// no bitwise operators available

	// boolean
	define(FloatObject::TYPENAME, Token::Type::AND,  BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::AND,  DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::AND,  FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::AND,  StringObject::TYPENAME,  BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NAND, BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NAND, DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NAND, FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NAND, StringObject::TYPENAME,  BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NOR,  BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NOR,  DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NOR,  FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NOR,  StringObject::TYPENAME,  BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::OR,   BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::OR,   DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::OR,   FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::OR,   StringObject::TYPENAME,  BoolObject::TYPENAME);

	// comparison
	define(FloatObject::TYPENAME, Token::Type::COMPARE_EQUAL,         DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_EQUAL,         FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_EQUAL,         Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_EQUAL,         Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER,       DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER,       FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER,       Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER,       Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS,          DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS,          FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS,          Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS,          Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_UNEQUAL,       DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_UNEQUAL,       FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int32Type::TYPENAME,     BoolObject::TYPENAME);

	// shift
	// no shift operators available

	// typecast
	define(FloatObject::TYPENAME, Token::Type::TYPECAST, BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::TYPECAST, DoubleObject::TYPENAME,  DoubleObject::TYPENAME);
	//define(FloatObject::TYPENAME, Token::Type::TYPECAST, EnumerationObject::TYPENAME, EnumerationObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::TYPECAST, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::TYPECAST, Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::TYPECAST, StringObject::TYPENAME,  StringObject::TYPENAME);

	// unary
	define(FloatObject::TYPENAME, Token::Type::MATH_ADDITION, _unary_, FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_SUBTRACT, _unary_, FloatObject::TYPENAME);
}

void TypeSystem::initInt16()
{
	// arithmetic
	define(Int16Type::TYPENAME, Token::Type::MATH_ADDITION, DoubleObject::TYPENAME,  DoubleObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_ADDITION, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_ADDITION, Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_ADDITION, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_DIVIDE,   DoubleObject::TYPENAME,  DoubleObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_DIVIDE,   FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_DIVIDE,   Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_DIVIDE,   Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MODULO,   Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MODULO,   Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MULTIPLY, DoubleObject::TYPENAME,  DoubleObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MULTIPLY, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MULTIPLY, Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MULTIPLY, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_SUBTRACT, DoubleObject::TYPENAME,  DoubleObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_SUBTRACT, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_SUBTRACT, Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_SUBTRACT, Int32Type::TYPENAME,     Int32Type::TYPENAME);


	// assign
	define(Int16Type::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME, Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME, Int16Type::TYPENAME);

	// bit
	define(Int16Type::TYPENAME, Token::Type::BITAND,        Int16Type::TYPENAME, Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::BITCOMPLEMENT, Int16Type::TYPENAME, Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::BITOR,         Int16Type::TYPENAME, Int16Type::TYPENAME);

	// boolean
	define(Int16Type::TYPENAME, Token::Type::AND,  BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::AND,  DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::AND,  FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::AND,  StringObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, StringObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  StringObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   StringObject::TYPENAME,  BoolObject::TYPENAME);

	// comparison
	define(Int16Type::TYPENAME, Token::Type::COMPARE_EQUAL,         Int16Type::TYPENAME, BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::COMPARE_GREATER,       Int16Type::TYPENAME, BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int16Type::TYPENAME, BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::COMPARE_LESS,          Int16Type::TYPENAME, BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int16Type::TYPENAME, BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int16Type::TYPENAME, BoolObject::TYPENAME);

	// shift
	// no shift operator available for user defined types

	// typecast
	define(Int16Type::TYPENAME, Token::Type::TYPECAST, BoolObject::TYPENAME,        BoolObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::TYPECAST, DoubleObject::TYPENAME,      DoubleObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::TYPECAST, EnumerationObject::TYPENAME, EnumerationObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::TYPECAST, FloatObject::TYPENAME,       FloatObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::TYPECAST, Int16Type::TYPENAME,         Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,         Int32Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::TYPECAST, StringObject::TYPENAME,      StringObject::TYPENAME);

	// unary
	define(Int16Type::TYPENAME, Token::Type::MATH_ADDITION, _unary_, Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_SUBTRACT, _unary_, Int16Type::TYPENAME);
}

void TypeSystem::initInt32()
{
	// arithmetic
	define(Int32Type::TYPENAME, Token::Type::MATH_ADDITION, DoubleObject::TYPENAME,  DoubleObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_ADDITION, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_ADDITION, Int16Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_ADDITION, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_DIVIDE,   DoubleObject::TYPENAME,  DoubleObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_DIVIDE,   FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_DIVIDE,   Int16Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_DIVIDE,   Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MODULO,   Int16Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MODULO,   Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MULTIPLY, DoubleObject::TYPENAME,  DoubleObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MULTIPLY, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MULTIPLY, Int16Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MULTIPLY, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_SUBTRACT, DoubleObject::TYPENAME,  DoubleObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_SUBTRACT, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_SUBTRACT, Int16Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_SUBTRACT, Int32Type::TYPENAME,     Int32Type::TYPENAME);

	// assign
	define(Int32Type::TYPENAME, Token::Type::ASSIGN, BoolObject::TYPENAME,   Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::ASSIGN, DoubleObject::TYPENAME, Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::ASSIGN, FloatObject::TYPENAME,  Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME,    Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME,    Int32Type::TYPENAME);

	// bit
	define(Int32Type::TYPENAME, Token::Type::BITAND,        Int32Type::TYPENAME, Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::BITCOMPLEMENT, Int32Type::TYPENAME, Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::BITOR,         Int32Type::TYPENAME, Int32Type::TYPENAME);

	// boolean
	define(Int32Type::TYPENAME, Token::Type::AND,  BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::AND,  DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::AND,  FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::AND,  StringObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, StringObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  StringObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   StringObject::TYPENAME,  BoolObject::TYPENAME);

	// comparison
	define(Int32Type::TYPENAME, Token::Type::COMPARE_EQUAL,         DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_EQUAL,         FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_EQUAL,         Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_EQUAL,         Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER,       DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER,       FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER,       Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER,       Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS,          DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS,          FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS,          Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS,          Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_UNEQUAL,       DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_UNEQUAL,       FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int32Type::TYPENAME,     BoolObject::TYPENAME);

	// shift
	// no shift operator available for user defined types

	// typecast
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, BoolObject::TYPENAME,        BoolObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, DoubleObject::TYPENAME,      DoubleObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, EnumerationObject::TYPENAME, EnumerationObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, FloatObject::TYPENAME,       FloatObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, Int16Type::TYPENAME,         Int16Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,         Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, StringObject::TYPENAME,      StringObject::TYPENAME);

	// unary
	define(Int32Type::TYPENAME, Token::Type::MATH_ADDITION, _unary_, Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_SUBTRACT, _unary_, Int32Type::TYPENAME);
}

void TypeSystem::initObject()
{
    // arithmetic
	// no arithmetic operator available

	// assign
	define(UserObject::TYPENAME, Token::Type::ASSIGN, UserObject::TYPENAME, UserObject::TYPENAME);

	// bit
	// no bitwise operators available

	// comparison
	define(UserObject::TYPENAME, Token::Type::COMPARE_EQUAL,   UserObject::TYPENAME, UserObject::TYPENAME);
	define(UserObject::TYPENAME, Token::Type::COMPARE_UNEQUAL, UserObject::TYPENAME, UserObject::TYPENAME);

	// shift
	// no shift operator available

	// typecast
	define(UserObject::TYPENAME, Token::Type::TYPECAST, UserObject::TYPENAME, UserObject::TYPENAME);

	// unary operations
	// no unary operator available
}

void TypeSystem::initString()
{
	// arithmetic
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, BoolObject::TYPENAME,    StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, DoubleObject::TYPENAME,  StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, FloatObject::TYPENAME,   StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, Int16Type::TYPENAME,     StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, Int32Type::TYPENAME,     StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, StringObject::TYPENAME,  StringObject::TYPENAME);

	// assign
	define(StringObject::TYPENAME, Token::Type::ASSIGN, BoolObject::TYPENAME,    StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::ASSIGN, DoubleObject::TYPENAME,  StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::ASSIGN, FloatObject::TYPENAME,   StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME,     StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME,     StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::ASSIGN, StringObject::TYPENAME,  StringObject::TYPENAME);

	// bit
	// no bitwise operators available

	// boolean
	define(StringObject::TYPENAME, Token::Type::AND,  BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::AND,  DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::AND,  FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::AND,  StringObject::TYPENAME,  BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NAND, BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NAND, DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NAND, FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NAND, StringObject::TYPENAME,  BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NOR,  BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NOR,  DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NOR,  FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NOR,  StringObject::TYPENAME,  BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OR,   BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OR,   DoubleObject::TYPENAME,  BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OR,   FloatObject::TYPENAME,   BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,     BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,     BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OR,   StringObject::TYPENAME,  BoolObject::TYPENAME);

	// comparison
	define(StringObject::TYPENAME, Token::Type::COMPARE_EQUAL,         StringObject::TYPENAME, BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::COMPARE_GREATER,       StringObject::TYPENAME, BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, StringObject::TYPENAME, BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::COMPARE_LESS,          StringObject::TYPENAME, BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    StringObject::TYPENAME, BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::COMPARE_UNEQUAL,       StringObject::TYPENAME, BoolObject::TYPENAME);

	// shift
	define(StringObject::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, BoolObject::TYPENAME,    StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, DoubleObject::TYPENAME,  StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, FloatObject::TYPENAME,   StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, Int16Type::TYPENAME,     StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, Int32Type::TYPENAME,     StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, StringObject::TYPENAME,  StringObject::TYPENAME);

	// typecast
	define(StringObject::TYPENAME, Token::Type::TYPECAST, BoolObject::TYPENAME,    BoolObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::TYPECAST, DoubleObject::TYPENAME,  DoubleObject::TYPENAME);
	//define(StringObject::TYPENAME, Token::Type::TYPECAST, EnumerationObject::TYPENAME, EnumerationObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::TYPECAST, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::TYPECAST, Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::TYPECAST, StringObject::TYPENAME,  StringObject::TYPENAME);

	// unary
	// no unary operator available
}


}
