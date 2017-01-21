
// Header
#include "UserObject.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


AtomicValue UserObject::DEFAULTVALUE = AtomicValue(VALUE_NONE);
std::string UserObject::TYPENAME = OBJECT;


UserObject::UserObject()
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE)
{
	mIsAtomicType = false;
	mIsConstructed = false;
}

UserObject::UserObject(const std::string& name, const std::string& filename, const std::string& type, bool isNull)
: Object(name, filename, type, AtomicValue(0))
{
	mIsAtomicType = false;
	mIsConstructed = false;
	mIsNull = isNull;
}

UserObject::UserObject(const Object& object)
: Object(object.getName(), object.Filename(), object.QualifiedTypename(), object.getValue())
{
	mIsAtomicType = false;
	mIsConstructed = false;
}

void UserObject::operator_assign(const Object *other)
{
	if ( other->isNull() ) {	// special handling for null object
		assign(*other);
		return;
	}

	if ( other->isInstanceOf(mQualifiedTypename) ) {
		assign(*other);
		return;
	}

	if ( isConstructed() ) {
		ParameterList params;
		params.push_back(Parameter::CreateRuntime(other->QualifiedOuterface(), other->getValue(), other->getReference()));

		::ObjectiveScript::MethodSymbol* operator_method = resolveMethod("operator=", params, true, Visibility::Private);
		if ( operator_method ) {
			Interpreter interpreter;
			interpreter.execute(static_cast<Common::Method*>(operator_method), params, mThis);

			return;
		}
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::ObjectiveScript::MethodSymbol* operator_method = other->resolveMethod("=operator", params, true, Visibility::Public);
	if ( operator_method ) {
		Interpreter interpreter;
		interpreter.execute(static_cast<Common::Method*>(operator_method), params, mThis);

		return;
	}

	throw Common::Exceptions::Exception(mQualifiedTypename + ".operator=: conversion from " + other->QualifiedTypename() + " to " + mQualifiedTypename + " not supported");
}

bool UserObject::operator_bool() const
{
	return isValid();
}

void UserObject::operator_divide(const Object *other)
{
	ParameterList params;
	params.push_back(Parameter::CreateRuntime(other->QualifiedOuterface(), other->getValue(), other->getReference()));

	Object tmp;
	this->execute(&tmp, "operator/", params, 0);
}

bool UserObject::operator_equal(const Object *other)
{
	ParameterList params;
	params.push_back(Parameter::CreateRuntime(other->QualifiedOuterface(), other->getValue(), other->getReference()));

	Object tmp;
	this->execute(&tmp, "operator==", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_greater(const Object *other)
{
	ParameterList params;
	params.push_back(Parameter::CreateRuntime(other->QualifiedOuterface(), other->getValue(), other->getReference()));

	Object tmp;
	this->execute(&tmp, "operator>", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_greater_equal(const Object *other)
{
	ParameterList params;
	params.push_back(Parameter::CreateRuntime(other->QualifiedOuterface(), other->getValue(), other->getReference()));

	Object tmp;
	this->execute(&tmp, "operator>=", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_less(const Object *other)
{
	ParameterList params;
	params.push_back(Parameter::CreateRuntime(other->QualifiedOuterface(), other->getValue(), other->getReference()));

	Object tmp;
	this->execute(&tmp, "operator<", params, 0);

	return tmp.isValid();
}

bool UserObject::operator_less_equal(const Object *other)
{
	ParameterList params;
	params.push_back(Parameter::CreateRuntime(other->QualifiedOuterface(), other->getValue(), other->getReference()));

	Object tmp;
	this->execute(&tmp, "operator<=", params, 0);

	return tmp.isValid();
}

void UserObject::operator_multiply(const Object *other)
{
	ParameterList params;
	params.push_back(Parameter::CreateRuntime(other->QualifiedOuterface(), other->getValue(), other->getReference()));

	Object tmp;
	this->execute(&tmp, "operator*", params, 0);
}

void UserObject::operator_plus(const Object *other)
{
	ParameterList params;
	params.push_back(Parameter::CreateRuntime(other->QualifiedOuterface(), other->getValue(), other->getReference()));

	Object tmp;
	this->execute(&tmp, "operator+", params, 0);
}

void UserObject::operator_subtract(const Object *other)
{
	ParameterList params;
	params.push_back(Parameter::CreateRuntime(other->QualifiedOuterface(), other->getValue(), other->getReference()));

	Object tmp;
	this->execute(&tmp, "operator-", params, 0);
}


}
}
