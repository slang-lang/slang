
// Header
#include "TypeSystem.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/BoolType.h>
#include <Core/Designtime/BuildInTypes/DoubleType.h>
#include <Core/Designtime/BuildInTypes/EnumerationType.h>
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
	define(BoolType::TYPENAME, Token::Type::ASSIGN, BoolType::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::ASSIGN, DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::ASSIGN, FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::ASSIGN, StringObject::TYPENAME,  BoolType::TYPENAME);

	// bit
	// no bitwise operators available

	// boolean
	define(BoolType::TYPENAME, Token::Type::AND,  BoolType::TYPENAME,   BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::AND,  DoubleType::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::AND,  FloatObject::TYPENAME,  BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::AND,  StringObject::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NAND, BoolType::TYPENAME,   BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NAND, DoubleType::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NAND, FloatObject::TYPENAME,  BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NAND, StringObject::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NOR,  BoolType::TYPENAME,   BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NOR,  DoubleType::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NOR,  FloatObject::TYPENAME,  BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NOR,  StringObject::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::OR,   BoolType::TYPENAME,   BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::OR,   DoubleType::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::OR,   FloatObject::TYPENAME,  BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::OR,   StringObject::TYPENAME, BoolType::TYPENAME);

	// comparison
	define(BoolType::TYPENAME, Token::Type::COMPARE_EQUAL,   BoolType::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::COMPARE_UNEQUAL, BoolType::TYPENAME, BoolType::TYPENAME);

	// shift
	// no shift operators available

	// typecast
	define(BoolType::TYPENAME, Token::Type::TYPECAST, BoolType::TYPENAME,   BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::TYPECAST, DoubleType::TYPENAME, DoubleType::TYPENAME);
	//define(BoolType::TYPENAME, Token::Type::TYPECAST, EnumerationType::TYPENAME, EnumerationType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::TYPECAST, FloatObject::TYPENAME,  FloatObject::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::TYPECAST, Int16Type::TYPENAME,    Int16Type::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,    Int32Type::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::TYPECAST, StringObject::TYPENAME, StringObject::TYPENAME);
}

void TypeSystem::initDouble()
{
	// arithmetic
	define(DoubleType::TYPENAME, Token::Type::MATH_ADDITION, DoubleType::TYPENAME, DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_ADDITION, FloatObject::TYPENAME,  DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_ADDITION, Int32Type::TYPENAME,    DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_DIVIDE,   DoubleType::TYPENAME, DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_DIVIDE,   FloatObject::TYPENAME,  DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_DIVIDE,   Int32Type::TYPENAME,    DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_MULTIPLY, DoubleType::TYPENAME, DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_MULTIPLY, FloatObject::TYPENAME,  DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_MULTIPLY, Int32Type::TYPENAME,    DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_SUBTRACT, DoubleType::TYPENAME, DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_SUBTRACT, FloatObject::TYPENAME,  DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_SUBTRACT, Int32Type::TYPENAME,    DoubleType::TYPENAME);

	// assign
	define(DoubleType::TYPENAME, Token::Type::ASSIGN, BoolType::TYPENAME,   DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::ASSIGN, DoubleType::TYPENAME, DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::ASSIGN, FloatObject::TYPENAME,  DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME,    DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME,    DoubleType::TYPENAME);

	// bit
	// no bitwise operators available

	// boolean
	define(DoubleType::TYPENAME, Token::Type::AND,  BoolType::TYPENAME,   BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::AND,  DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::AND,  FloatObject::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::AND,  StringObject::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NAND, BoolType::TYPENAME,   BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NAND, DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NAND, FloatObject::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NAND, StringObject::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NOR,  BoolType::TYPENAME,   BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NOR,  DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NOR,  FloatObject::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NOR,  StringObject::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::OR,   BoolType::TYPENAME,   BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::OR,   DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::OR,   FloatObject::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::OR,   StringObject::TYPENAME, BoolType::TYPENAME);

	// comparison
	define(DoubleType::TYPENAME, Token::Type::COMPARE_EQUAL,         DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_EQUAL,         FloatObject::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_EQUAL,         Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_EQUAL,         Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER,       DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER,       FloatObject::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER,       Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER,       Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, FloatObject::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS,          DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS,          FloatObject::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS,          Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS,          Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    FloatObject::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_UNEQUAL,       DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_UNEQUAL,       FloatObject::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int32Type::TYPENAME,    BoolType::TYPENAME);

	// shift
	// no shift operators available

	// typecast
	define(DoubleType::TYPENAME, Token::Type::TYPECAST, BoolType::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::TYPECAST, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	//define(DoubleType::TYPENAME, Token::Type::TYPECAST, EnumerationType::TYPENAME, EnumerationType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::TYPECAST, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::TYPECAST, StringObject::TYPENAME,  StringObject::TYPENAME);

	// unary
	define(DoubleType::TYPENAME, Token::Type::MATH_ADDITION, _unary_, DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_SUBTRACT, _unary_, DoubleType::TYPENAME);
}

void TypeSystem::initEnumeration()
{
    // assign
    define(EnumerationType::TYPENAME, Token::Type::ASSIGN, EnumerationType::TYPENAME, EnumerationType::TYPENAME);

    // bit
	// no bitwise operators available

    // shift
    // no shift operators available

	// typecast
	define(EnumerationType::TYPENAME, Token::Type::TYPECAST, BoolType::TYPENAME,        BoolType::TYPENAME);
	define(EnumerationType::TYPENAME, Token::Type::TYPECAST, DoubleType::TYPENAME,      DoubleType::TYPENAME);
	//define(EnumerationType::TYPENAME, Token::Type::TYPECAST, EnumerationType::TYPENAME, EnumerationType::TYPENAME);
	define(EnumerationType::TYPENAME, Token::Type::TYPECAST, FloatObject::TYPENAME,       FloatObject::TYPENAME);
	define(EnumerationType::TYPENAME, Token::Type::TYPECAST, Int16Type::TYPENAME,         Int16Type::TYPENAME);
	define(EnumerationType::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,         Int32Type::TYPENAME);
	define(EnumerationType::TYPENAME, Token::Type::TYPECAST, StringObject::TYPENAME,      StringObject::TYPENAME);

	// unary
	// no unary operators available
}

void TypeSystem::initFloat()
{
	// assign
	define(FloatObject::TYPENAME, Token::Type::ASSIGN, BoolType::TYPENAME,    FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::ASSIGN, DoubleType::TYPENAME,  FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::ASSIGN, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME,     FloatObject::TYPENAME);

	// arithmetic
	define(FloatObject::TYPENAME, Token::Type::MATH_ADDITION, DoubleType::TYPENAME,  FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_ADDITION, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_ADDITION, Int16Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_ADDITION, Int32Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_DIVIDE,   DoubleType::TYPENAME,  FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_DIVIDE,   FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_DIVIDE,   Int16Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_DIVIDE,   Int32Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_MULTIPLY, DoubleType::TYPENAME,  FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_MULTIPLY, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_MULTIPLY, Int16Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_MULTIPLY, Int32Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_SUBTRACT, DoubleType::TYPENAME,  FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_SUBTRACT, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_SUBTRACT, Int16Type::TYPENAME,     FloatObject::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::MATH_SUBTRACT, Int32Type::TYPENAME,     FloatObject::TYPENAME);

	// bit
	// no bitwise operators available

	// boolean
	define(FloatObject::TYPENAME, Token::Type::AND,  BoolType::TYPENAME,    BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::AND,  DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::AND,  FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::AND,  StringObject::TYPENAME,  BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NAND, BoolType::TYPENAME,    BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NAND, DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NAND, FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NAND, StringObject::TYPENAME,  BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NOR,  BoolType::TYPENAME,    BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NOR,  DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NOR,  FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::NOR,  StringObject::TYPENAME,  BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::OR,   BoolType::TYPENAME,    BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::OR,   DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::OR,   FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::OR,   StringObject::TYPENAME,  BoolType::TYPENAME);

	// comparison
	define(FloatObject::TYPENAME, Token::Type::COMPARE_EQUAL,         DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_EQUAL,         FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_EQUAL,         Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_EQUAL,         Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER,       DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER,       FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER,       Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER,       Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS,          DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS,          FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS,          Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS,          Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_UNEQUAL,       DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_UNEQUAL,       FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int32Type::TYPENAME,     BoolType::TYPENAME);

	// shift
	// no shift operators available

	// typecast
	define(FloatObject::TYPENAME, Token::Type::TYPECAST, BoolType::TYPENAME,    BoolType::TYPENAME);
	define(FloatObject::TYPENAME, Token::Type::TYPECAST, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	//define(FloatObject::TYPENAME, Token::Type::TYPECAST, EnumerationType::TYPENAME, EnumerationType::TYPENAME);
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
	define(Int16Type::TYPENAME, Token::Type::MATH_ADDITION, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_ADDITION, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_ADDITION, Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_ADDITION, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_DIVIDE,   DoubleType::TYPENAME,  DoubleType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_DIVIDE,   FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_DIVIDE,   Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_DIVIDE,   Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MODULO,   Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MODULO,   Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MULTIPLY, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MULTIPLY, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MULTIPLY, Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MULTIPLY, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_SUBTRACT, DoubleType::TYPENAME,  DoubleType::TYPENAME);
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
	define(Int16Type::TYPENAME, Token::Type::AND,  BoolType::TYPENAME,    BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::AND,  DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::AND,  FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::AND,  StringObject::TYPENAME,  BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, BoolType::TYPENAME,    BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, StringObject::TYPENAME,  BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  BoolType::TYPENAME,    BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  StringObject::TYPENAME,  BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   BoolType::TYPENAME,    BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   StringObject::TYPENAME,  BoolType::TYPENAME);

	// comparison
	define(Int16Type::TYPENAME, Token::Type::COMPARE_EQUAL,         Int16Type::TYPENAME, BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::COMPARE_GREATER,       Int16Type::TYPENAME, BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int16Type::TYPENAME, BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::COMPARE_LESS,          Int16Type::TYPENAME, BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int16Type::TYPENAME, BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int16Type::TYPENAME, BoolType::TYPENAME);

	// shift
	// no shift operator available for user defined types

	// typecast
	define(Int16Type::TYPENAME, Token::Type::TYPECAST, BoolType::TYPENAME,        BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::TYPECAST, DoubleType::TYPENAME,      DoubleType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::TYPECAST, EnumerationType::TYPENAME, EnumerationType::TYPENAME);
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
	define(Int32Type::TYPENAME, Token::Type::MATH_ADDITION, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_ADDITION, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_ADDITION, Int16Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_ADDITION, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_DIVIDE,   DoubleType::TYPENAME,  DoubleType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_DIVIDE,   FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_DIVIDE,   Int16Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_DIVIDE,   Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MODULO,   Int16Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MODULO,   Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MULTIPLY, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MULTIPLY, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MULTIPLY, Int16Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MULTIPLY, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_SUBTRACT, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_SUBTRACT, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_SUBTRACT, Int16Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_SUBTRACT, Int32Type::TYPENAME,     Int32Type::TYPENAME);

	// assign
	define(Int32Type::TYPENAME, Token::Type::ASSIGN, BoolType::TYPENAME,   Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::ASSIGN, DoubleType::TYPENAME, Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::ASSIGN, FloatObject::TYPENAME,  Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME,    Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME,    Int32Type::TYPENAME);

	// bit
	define(Int32Type::TYPENAME, Token::Type::BITAND,        Int32Type::TYPENAME, Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::BITCOMPLEMENT, Int32Type::TYPENAME, Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::BITOR,         Int32Type::TYPENAME, Int32Type::TYPENAME);

	// boolean
	define(Int32Type::TYPENAME, Token::Type::AND,  BoolType::TYPENAME,    BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::AND,  DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::AND,  FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::AND,  StringObject::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, BoolType::TYPENAME,    BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, StringObject::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  BoolType::TYPENAME,    BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  StringObject::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   BoolType::TYPENAME,    BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   StringObject::TYPENAME,  BoolType::TYPENAME);

	// comparison
	define(Int32Type::TYPENAME, Token::Type::COMPARE_EQUAL,         DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_EQUAL,         FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_EQUAL,         Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_EQUAL,         Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER,       DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER,       FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER,       Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER,       Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS,          DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS,          FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS,          Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS,          Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_UNEQUAL,       DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_UNEQUAL,       FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int32Type::TYPENAME,     BoolType::TYPENAME);

	// shift
	// no shift operator available for user defined types

	// typecast
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, BoolType::TYPENAME,        BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, DoubleType::TYPENAME,      DoubleType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, EnumerationType::TYPENAME, EnumerationType::TYPENAME);
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
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, BoolType::TYPENAME,    StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, DoubleType::TYPENAME,  StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, FloatObject::TYPENAME,   StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, Int16Type::TYPENAME,     StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, Int32Type::TYPENAME,     StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::MATH_ADDITION, StringObject::TYPENAME,  StringObject::TYPENAME);

	// assign
	define(StringObject::TYPENAME, Token::Type::ASSIGN, BoolType::TYPENAME,    StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::ASSIGN, DoubleType::TYPENAME,  StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::ASSIGN, FloatObject::TYPENAME,   StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME,     StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME,     StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::ASSIGN, StringObject::TYPENAME,  StringObject::TYPENAME);

	// bit
	// no bitwise operators available

	// boolean
	define(StringObject::TYPENAME, Token::Type::AND,  BoolType::TYPENAME,    BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::AND,  DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::AND,  FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::AND,  StringObject::TYPENAME,  BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NAND, BoolType::TYPENAME,    BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NAND, DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NAND, FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NAND, StringObject::TYPENAME,  BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NOR,  BoolType::TYPENAME,    BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NOR,  DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NOR,  FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::NOR,  StringObject::TYPENAME,  BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OR,   BoolType::TYPENAME,    BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OR,   DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OR,   FloatObject::TYPENAME,   BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OR,   StringObject::TYPENAME,  BoolType::TYPENAME);

	// comparison
	define(StringObject::TYPENAME, Token::Type::COMPARE_EQUAL,         StringObject::TYPENAME, BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::COMPARE_GREATER,       StringObject::TYPENAME, BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, StringObject::TYPENAME, BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::COMPARE_LESS,          StringObject::TYPENAME, BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    StringObject::TYPENAME, BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::COMPARE_UNEQUAL,       StringObject::TYPENAME, BoolType::TYPENAME);

	// shift
	define(StringObject::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, BoolType::TYPENAME,    StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, DoubleType::TYPENAME,  StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, FloatObject::TYPENAME,   StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, Int16Type::TYPENAME,     StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, Int32Type::TYPENAME,     StringObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, StringObject::TYPENAME,  StringObject::TYPENAME);

	// typecast
	define(StringObject::TYPENAME, Token::Type::TYPECAST, BoolType::TYPENAME,    BoolType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::TYPECAST, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	//define(StringObject::TYPENAME, Token::Type::TYPECAST, EnumerationType::TYPENAME, EnumerationType::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::TYPECAST, FloatObject::TYPENAME,   FloatObject::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::TYPECAST, Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(StringObject::TYPENAME, Token::Type::TYPECAST, StringObject::TYPENAME,  StringObject::TYPENAME);

	// unary
	// no unary operator available
}


}
