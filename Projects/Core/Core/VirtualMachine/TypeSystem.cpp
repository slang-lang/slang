
// Header
#include "TypeSystem.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/BoolType.h>
#include <Core/Designtime/BuildInTypes/DoubleType.h>
#include <Core/Designtime/BuildInTypes/EnumerationType.h>
#include <Core/Designtime/BuildInTypes/FloatType.h>
#include <Core/Designtime/BuildInTypes/Int16Type.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Designtime/BuildInTypes/UserType.h>
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
	define(BoolType::TYPENAME, Token::Type::ASSIGN, FloatType::TYPENAME,   BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::ASSIGN, StringType::TYPENAME,  BoolType::TYPENAME);

	// bit
	// no bitwise operators available

	// boolean
	define(BoolType::TYPENAME, Token::Type::AND,  BoolType::TYPENAME,   BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::AND,  DoubleType::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::AND,  FloatType::TYPENAME,  BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::AND,  StringType::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NAND, BoolType::TYPENAME,   BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NAND, DoubleType::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NAND, FloatType::TYPENAME,  BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NAND, StringType::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NOR,  BoolType::TYPENAME,   BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NOR,  DoubleType::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NOR,  FloatType::TYPENAME,  BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::NOR,  StringType::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::OR,   BoolType::TYPENAME,   BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::OR,   DoubleType::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::OR,   FloatType::TYPENAME,  BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::OR,   StringType::TYPENAME, BoolType::TYPENAME);

	// comparison
	define(BoolType::TYPENAME, Token::Type::COMPARE_EQUAL,   BoolType::TYPENAME, BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::COMPARE_UNEQUAL, BoolType::TYPENAME, BoolType::TYPENAME);

	// shift
	// no shift operators available

	// typecast
	define(BoolType::TYPENAME, Token::Type::TYPECAST, BoolType::TYPENAME,   BoolType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::TYPECAST, DoubleType::TYPENAME, DoubleType::TYPENAME);
	//define(BoolType::TYPENAME, Token::Type::TYPECAST, EnumerationType::TYPENAME, EnumerationType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::TYPECAST, FloatType::TYPENAME,  FloatType::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::TYPECAST, Int16Type::TYPENAME,    Int16Type::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,    Int32Type::TYPENAME);
	define(BoolType::TYPENAME, Token::Type::TYPECAST, StringType::TYPENAME, StringType::TYPENAME);
}

void TypeSystem::initDouble()
{
	// arithmetic
	define(DoubleType::TYPENAME, Token::Type::MATH_ADDITION, DoubleType::TYPENAME, DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_ADDITION, FloatType::TYPENAME,  DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_ADDITION, Int32Type::TYPENAME,    DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_DIVIDE,   DoubleType::TYPENAME, DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_DIVIDE,   FloatType::TYPENAME,  DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_DIVIDE,   Int32Type::TYPENAME,    DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_MULTIPLY, DoubleType::TYPENAME, DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_MULTIPLY, FloatType::TYPENAME,  DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_MULTIPLY, Int32Type::TYPENAME,    DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_SUBTRACT, DoubleType::TYPENAME, DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_SUBTRACT, FloatType::TYPENAME,  DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::MATH_SUBTRACT, Int32Type::TYPENAME,    DoubleType::TYPENAME);

	// assign
	define(DoubleType::TYPENAME, Token::Type::ASSIGN, BoolType::TYPENAME,   DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::ASSIGN, DoubleType::TYPENAME, DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::ASSIGN, FloatType::TYPENAME,  DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME,    DoubleType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME,    DoubleType::TYPENAME);

	// bit
	// no bitwise operators available

	// boolean
	define(DoubleType::TYPENAME, Token::Type::AND,  BoolType::TYPENAME,   BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::AND,  DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::AND,  FloatType::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::AND,  StringType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NAND, BoolType::TYPENAME,   BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NAND, DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NAND, FloatType::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NAND, StringType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NOR,  BoolType::TYPENAME,   BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NOR,  DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NOR,  FloatType::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::NOR,  StringType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::OR,   BoolType::TYPENAME,   BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::OR,   DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::OR,   FloatType::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::OR,   StringType::TYPENAME, BoolType::TYPENAME);

	// comparison
	define(DoubleType::TYPENAME, Token::Type::COMPARE_EQUAL,         DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_EQUAL,         FloatType::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_EQUAL,         Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_EQUAL,         Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER,       DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER,       FloatType::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER,       Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER,       Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, FloatType::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS,          DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS,          FloatType::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS,          Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS,          Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    FloatType::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int32Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_UNEQUAL,       DoubleType::TYPENAME, BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_UNEQUAL,       FloatType::TYPENAME,  BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int16Type::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int32Type::TYPENAME,    BoolType::TYPENAME);

	// shift
	// no shift operators available

	// typecast
	define(DoubleType::TYPENAME, Token::Type::TYPECAST, BoolType::TYPENAME,    BoolType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::TYPECAST, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	//define(DoubleType::TYPENAME, Token::Type::TYPECAST, EnumerationType::TYPENAME, EnumerationType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::TYPECAST, FloatType::TYPENAME,   FloatType::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(DoubleType::TYPENAME, Token::Type::TYPECAST, StringType::TYPENAME,  StringType::TYPENAME);

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
	define(EnumerationType::TYPENAME, Token::Type::TYPECAST, FloatType::TYPENAME,       FloatType::TYPENAME);
	define(EnumerationType::TYPENAME, Token::Type::TYPECAST, Int16Type::TYPENAME,         Int16Type::TYPENAME);
	define(EnumerationType::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,         Int32Type::TYPENAME);
	define(EnumerationType::TYPENAME, Token::Type::TYPECAST, StringType::TYPENAME,      StringType::TYPENAME);

	// unary
	// no unary operators available
}

void TypeSystem::initFloat()
{
	// assign
	define(FloatType::TYPENAME, Token::Type::ASSIGN, BoolType::TYPENAME,    FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::ASSIGN, DoubleType::TYPENAME,  FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::ASSIGN, FloatType::TYPENAME,   FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME,     FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME,     FloatType::TYPENAME);

	// arithmetic
	define(FloatType::TYPENAME, Token::Type::MATH_ADDITION, DoubleType::TYPENAME,  FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_ADDITION, FloatType::TYPENAME,   FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_ADDITION, Int16Type::TYPENAME,     FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_ADDITION, Int32Type::TYPENAME,     FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_DIVIDE,   DoubleType::TYPENAME,  FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_DIVIDE,   FloatType::TYPENAME,   FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_DIVIDE,   Int16Type::TYPENAME,     FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_DIVIDE,   Int32Type::TYPENAME,     FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_MULTIPLY, DoubleType::TYPENAME,  FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_MULTIPLY, FloatType::TYPENAME,   FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_MULTIPLY, Int16Type::TYPENAME,     FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_MULTIPLY, Int32Type::TYPENAME,     FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_SUBTRACT, DoubleType::TYPENAME,  FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_SUBTRACT, FloatType::TYPENAME,   FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_SUBTRACT, Int16Type::TYPENAME,     FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_SUBTRACT, Int32Type::TYPENAME,     FloatType::TYPENAME);

	// bit
	// no bitwise operators available

	// boolean
	define(FloatType::TYPENAME, Token::Type::AND,  BoolType::TYPENAME,    BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::AND,  DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::AND,  FloatType::TYPENAME,   BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::AND,  StringType::TYPENAME,  BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::NAND, BoolType::TYPENAME,    BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::NAND, DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::NAND, FloatType::TYPENAME,   BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::NAND, StringType::TYPENAME,  BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::NOR,  BoolType::TYPENAME,    BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::NOR,  DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::NOR,  FloatType::TYPENAME,   BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::NOR,  StringType::TYPENAME,  BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::OR,   BoolType::TYPENAME,    BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::OR,   DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::OR,   FloatType::TYPENAME,   BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::OR,   StringType::TYPENAME,  BoolType::TYPENAME);

	// comparison
	define(FloatType::TYPENAME, Token::Type::COMPARE_EQUAL,         DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_EQUAL,         FloatType::TYPENAME,   BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_EQUAL,         Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_EQUAL,         Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_GREATER,       DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_GREATER,       FloatType::TYPENAME,   BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_GREATER,       Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_GREATER,       Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, FloatType::TYPENAME,   BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_LESS,          DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_LESS,          FloatType::TYPENAME,   BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_LESS,          Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_LESS,          Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    FloatType::TYPENAME,   BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_UNEQUAL,       DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_UNEQUAL,       FloatType::TYPENAME,   BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int32Type::TYPENAME,     BoolType::TYPENAME);

	// shift
	// no shift operators available

	// typecast
	define(FloatType::TYPENAME, Token::Type::TYPECAST, BoolType::TYPENAME,    BoolType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::TYPECAST, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	//define(FloatType::TYPENAME, Token::Type::TYPECAST, EnumerationType::TYPENAME, EnumerationType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::TYPECAST, FloatType::TYPENAME,   FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::TYPECAST, Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::TYPECAST, StringType::TYPENAME,  StringType::TYPENAME);

	// unary
	define(FloatType::TYPENAME, Token::Type::MATH_ADDITION, _unary_, FloatType::TYPENAME);
	define(FloatType::TYPENAME, Token::Type::MATH_SUBTRACT, _unary_, FloatType::TYPENAME);
}

void TypeSystem::initInt16()
{
	// arithmetic
	define(Int16Type::TYPENAME, Token::Type::MATH_ADDITION, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_ADDITION, FloatType::TYPENAME,   FloatType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_ADDITION, Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_ADDITION, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_DIVIDE,   DoubleType::TYPENAME,  DoubleType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_DIVIDE,   FloatType::TYPENAME,   FloatType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_DIVIDE,   Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_DIVIDE,   Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MODULO,   Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MODULO,   Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MULTIPLY, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MULTIPLY, FloatType::TYPENAME,   FloatType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MULTIPLY, Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_MULTIPLY, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_SUBTRACT, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_SUBTRACT, FloatType::TYPENAME,   FloatType::TYPENAME);
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
	define(Int16Type::TYPENAME, Token::Type::AND,  FloatType::TYPENAME,   BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::AND,  StringType::TYPENAME,  BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, BoolType::TYPENAME,    BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, FloatType::TYPENAME,   BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NAND, StringType::TYPENAME,  BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  BoolType::TYPENAME,    BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  FloatType::TYPENAME,   BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::NOR,  StringType::TYPENAME,  BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   BoolType::TYPENAME,    BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   FloatType::TYPENAME,   BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::OR,   StringType::TYPENAME,  BoolType::TYPENAME);

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
	define(Int16Type::TYPENAME, Token::Type::TYPECAST, FloatType::TYPENAME,       FloatType::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::TYPECAST, Int16Type::TYPENAME,         Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,         Int32Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::TYPECAST, StringType::TYPENAME,      StringType::TYPENAME);

	// unary
	define(Int16Type::TYPENAME, Token::Type::MATH_ADDITION, _unary_, Int16Type::TYPENAME);
	define(Int16Type::TYPENAME, Token::Type::MATH_SUBTRACT, _unary_, Int16Type::TYPENAME);
}

void TypeSystem::initInt32()
{
	// arithmetic
	define(Int32Type::TYPENAME, Token::Type::MATH_ADDITION, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_ADDITION, FloatType::TYPENAME,   FloatType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_ADDITION, Int16Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_ADDITION, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_DIVIDE,   DoubleType::TYPENAME,  DoubleType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_DIVIDE,   FloatType::TYPENAME,   FloatType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_DIVIDE,   Int16Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_DIVIDE,   Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MODULO,   Int16Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MODULO,   Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MULTIPLY, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MULTIPLY, FloatType::TYPENAME,   FloatType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MULTIPLY, Int16Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_MULTIPLY, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_SUBTRACT, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_SUBTRACT, FloatType::TYPENAME,   FloatType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_SUBTRACT, Int16Type::TYPENAME,     Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_SUBTRACT, Int32Type::TYPENAME,     Int32Type::TYPENAME);

	// assign
	define(Int32Type::TYPENAME, Token::Type::ASSIGN, BoolType::TYPENAME,   Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::ASSIGN, DoubleType::TYPENAME, Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::ASSIGN, FloatType::TYPENAME,  Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME,    Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME,    Int32Type::TYPENAME);

	// bit
	define(Int32Type::TYPENAME, Token::Type::BITAND,        Int32Type::TYPENAME, Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::BITCOMPLEMENT, Int32Type::TYPENAME, Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::BITOR,         Int32Type::TYPENAME, Int32Type::TYPENAME);

	// boolean
	define(Int32Type::TYPENAME, Token::Type::AND,  BoolType::TYPENAME,    BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::AND,  DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::AND,  FloatType::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::AND,  StringType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, BoolType::TYPENAME,    BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, FloatType::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NAND, StringType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  BoolType::TYPENAME,    BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  FloatType::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::NOR,  StringType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   BoolType::TYPENAME,    BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   FloatType::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::OR,   StringType::TYPENAME,  BoolType::TYPENAME);

	// comparison
	define(Int32Type::TYPENAME, Token::Type::COMPARE_EQUAL,         DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_EQUAL,         FloatType::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_EQUAL,         Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_EQUAL,         Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER,       DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER,       FloatType::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER,       Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER,       Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, FloatType::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS,          DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS,          FloatType::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS,          Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS,          Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    FloatType::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_UNEQUAL,       DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_UNEQUAL,       FloatType::TYPENAME,   BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::COMPARE_UNEQUAL,       Int32Type::TYPENAME,     BoolType::TYPENAME);

	// shift
	// no shift operator available for user defined types

	// typecast
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, BoolType::TYPENAME,        BoolType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, DoubleType::TYPENAME,      DoubleType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, EnumerationType::TYPENAME, EnumerationType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, FloatType::TYPENAME,       FloatType::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, Int16Type::TYPENAME,         Int16Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,         Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::TYPECAST, StringType::TYPENAME,      StringType::TYPENAME);

	// unary
	define(Int32Type::TYPENAME, Token::Type::MATH_ADDITION, _unary_, Int32Type::TYPENAME);
	define(Int32Type::TYPENAME, Token::Type::MATH_SUBTRACT, _unary_, Int32Type::TYPENAME);
}

void TypeSystem::initObject()
{
    // arithmetic
	// no arithmetic operator available

	// assign
	define(UserType::TYPENAME, Token::Type::ASSIGN, UserType::TYPENAME, UserType::TYPENAME);

	// bit
	// no bitwise operators available

	// comparison
	define(UserType::TYPENAME, Token::Type::COMPARE_EQUAL,   UserType::TYPENAME, UserType::TYPENAME);
	define(UserType::TYPENAME, Token::Type::COMPARE_UNEQUAL, UserType::TYPENAME, UserType::TYPENAME);

	// shift
	// no shift operator available

	// typecast
	define(UserType::TYPENAME, Token::Type::TYPECAST, UserType::TYPENAME, UserType::TYPENAME);

	// unary operations
	// no unary operator available
}

void TypeSystem::initString()
{
	// arithmetic
	define(StringType::TYPENAME, Token::Type::MATH_ADDITION, BoolType::TYPENAME,    StringType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::MATH_ADDITION, DoubleType::TYPENAME,  StringType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::MATH_ADDITION, FloatType::TYPENAME,   StringType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::MATH_ADDITION, Int16Type::TYPENAME,     StringType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::MATH_ADDITION, Int32Type::TYPENAME,     StringType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::MATH_ADDITION, StringType::TYPENAME,  StringType::TYPENAME);

	// assign
	define(StringType::TYPENAME, Token::Type::ASSIGN, BoolType::TYPENAME,    StringType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::ASSIGN, DoubleType::TYPENAME,  StringType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::ASSIGN, FloatType::TYPENAME,   StringType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::ASSIGN, Int16Type::TYPENAME,     StringType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::ASSIGN, Int32Type::TYPENAME,     StringType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::ASSIGN, StringType::TYPENAME,  StringType::TYPENAME);

	// bit
	// no bitwise operators available

	// boolean
	define(StringType::TYPENAME, Token::Type::AND,  BoolType::TYPENAME,    BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::AND,  DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::AND,  FloatType::TYPENAME,   BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::AND,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::AND,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::AND,  StringType::TYPENAME,  BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::NAND, BoolType::TYPENAME,    BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::NAND, DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::NAND, FloatType::TYPENAME,   BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::NAND, Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::NAND, Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::NAND, StringType::TYPENAME,  BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::NOR,  BoolType::TYPENAME,    BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::NOR,  DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::NOR,  FloatType::TYPENAME,   BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::NOR,  Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::NOR,  Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::NOR,  StringType::TYPENAME,  BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::OR,   BoolType::TYPENAME,    BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::OR,   DoubleType::TYPENAME,  BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::OR,   FloatType::TYPENAME,   BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::OR,   Int16Type::TYPENAME,     BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::OR,   Int32Type::TYPENAME,     BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::OR,   StringType::TYPENAME,  BoolType::TYPENAME);

	// comparison
	define(StringType::TYPENAME, Token::Type::COMPARE_EQUAL,         StringType::TYPENAME, BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::COMPARE_GREATER,       StringType::TYPENAME, BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::COMPARE_GREATER_EQUAL, StringType::TYPENAME, BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::COMPARE_LESS,          StringType::TYPENAME, BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::COMPARE_LESS_EQUAL,    StringType::TYPENAME, BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::COMPARE_UNEQUAL,       StringType::TYPENAME, BoolType::TYPENAME);

	// shift
	define(StringType::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, BoolType::TYPENAME,    StringType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, DoubleType::TYPENAME,  StringType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, FloatType::TYPENAME,   StringType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, Int16Type::TYPENAME,     StringType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, Int32Type::TYPENAME,     StringType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::OPERATOR_SHIFT_LEFT, StringType::TYPENAME,  StringType::TYPENAME);

	// typecast
	define(StringType::TYPENAME, Token::Type::TYPECAST, BoolType::TYPENAME,    BoolType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::TYPECAST, DoubleType::TYPENAME,  DoubleType::TYPENAME);
	//define(StringType::TYPENAME, Token::Type::TYPECAST, EnumerationType::TYPENAME, EnumerationType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::TYPECAST, FloatType::TYPENAME,   FloatType::TYPENAME);
	define(StringType::TYPENAME, Token::Type::TYPECAST, Int16Type::TYPENAME,     Int16Type::TYPENAME);
	define(StringType::TYPENAME, Token::Type::TYPECAST, Int32Type::TYPENAME,     Int32Type::TYPENAME);
	define(StringType::TYPENAME, Token::Type::TYPECAST, StringType::TYPENAME,  StringType::TYPENAME);

	// unary
	// no unary operator available
}


}
