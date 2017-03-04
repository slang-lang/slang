
// Header
#include "TypeSystem.h"

// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/DoubleObject.h>
#include <Core/Designtime/BuildInTypes/FloatObject.h>
#include <Core/Designtime/BuildInTypes/GenericObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>

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
	(void)left;
	(void)operation;
	(void)result;
	(void)right;
}

void TypeSystem::deinit()
{
	// nothing to do here atm
}

std::string TypeSystem::getType(const std::string& left, Token::Type::E operation, const std::string& right) const
{
	(void)left;
	(void)operation;
	(void)right;

	return "";
}

void TypeSystem::init()
{
	// int
	define(IntegerObject::TYPENAME, Token::Type::MATH_ADDITION, IntegerObject::TYPENAME, IntegerObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::MATH_DIVIDE, IntegerObject::TYPENAME, IntegerObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::MATH_MODULO, IntegerObject::TYPENAME, IntegerObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::MATH_MULTIPLY, IntegerObject::TYPENAME, IntegerObject::TYPENAME);
	define(IntegerObject::TYPENAME, Token::Type::MATH_SUBTRACT, IntegerObject::TYPENAME, IntegerObject::TYPENAME);
}


}
