
// Header
#include "Object.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Consts.h"
#include "Memory.h"
#include "Repository.h"
#include "Symbol.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


Object::Object()
: MethodScope(ANONYMOUS_OBJECT, 0),
  ObjectSymbol(ANONYMOUS_OBJECT),
  mIsAtomicType(true),
  mRepository(0),
  mValue(VALUE_NONE),
  mConstructed(false)
{
}

Object::Object(const Object& other)
: MethodScope(other.getName(), 0),
  ObjectSymbol(other.getName()),
  RTTI(other.Typename(), other.Filename()),
  mIsAtomicType(other.mIsAtomicType),
  mRepository(other.mRepository),
  mConstructed(other.mConstructed)
{
	setValue(other.getValue());

	setConst(other.isConst());
	setFinal(other.isFinal());
	setMember(other.isMember());

	// register this
	define(KEYWORD_THIS, this);

	// register new members
	for ( Symbols::const_iterator it = other.mSymbols.begin(); it != other.mSymbols.end(); ++it ) {
		if ( it->first == KEYWORD_THIS || !it->second || it->second->getType() != Symbol::IType::ObjectSymbol ) {
			continue;
		}

		Object *symbol = static_cast<Object*>(it->second);

		// create object instance
		Object *object = mRepository->createInstance(symbol->Typename(), symbol->getName());

		// and fill it with life
		*object = *symbol;

		mRepository->removeReference(symbol);

		define(object->getName(), object);
	}

	// register new methods
	for ( MethodCollection::const_iterator it = other.mMethods.begin(); it != other.mMethods.end(); ++it ) {
		Method *method = new Method(this, (*it)->getName(), (*it)->getTypeName());
		*method = *(*it);

		method->define(KEYWORD_THIS, this);
		method->setOwner(this);

		defineMethod(method);
	}
}

Object::Object(const std::string& name, const std::string& filename, const std::string& type, const std::string& value)
: MethodScope(name, 0),
  ObjectSymbol(name),
  RTTI(type, filename),
  mIsAtomicType(true),
  mRepository(0),
  mValue(value),
  mConstructed(false)
{
}

Object::~Object()
{
	garbageCollector();
}

void Object::operator= (const Object& other)
{
	if ( this != &other ) {
		if ( !mConstructed ) {
			mConstructed = other.mConstructed;
		}
		if ( !mRepository ) {
			mRepository = other.mRepository;
		}

		mFilename = other.mFilename;
		mName = other.mName;
		mTypename = other.mTypename;

		setValue(other.getValue());

		//setConst(other.isConst());
		//setFinal(other.isFinal());
		//setMember(other.isMember());

		garbageCollector();

		// register this
		define(KEYWORD_THIS, this);

		// register new members
		for ( Symbols::const_iterator it = other.mSymbols.begin(); it != other.mSymbols.end(); ++it ) {
			if ( it->first == KEYWORD_THIS ) {
				continue;
			}

			define(it->first, it->second);
		}

		// register new methods
		for ( MethodCollection::const_iterator it = other.mMethods.begin(); it != other.mMethods.end(); ++it ) {
			Method *method = new Method(this, (*it)->getName(), (*it)->getTypeName());
			*method = *(*it);

			method->define(KEYWORD_THIS, this);
			method->setOwner(this);

			defineMethod(method);
		}
	}
}

void Object::Constructor(const ParameterList& params)
{
	if ( mConstructed ) {
		throw Utils::Exceptions::Exception("can not construct object '" + getName() + "' multiple times");
	}

	// only execute constructor if one is present
	Method *constructor = static_cast<Method*>(resolveMethod(Typename(), params));
	if ( constructor ) {
		VoidObject tmp;
		ControlFlow::E controlflow = constructor->execute(params, &tmp);

		if ( controlflow != ControlFlow::Normal ) {
			// uups
		}
	}

	// set after executing constructor in case any exceptions have been thrown
	mConstructed = true;
}

void Object::Destructor()
{
	if ( mConstructed ) {
		ParameterList params;

		// only execute destructor if one is present
		Method *constructor = static_cast<Method*>(resolveMethod("~" + Typename(), params));
		if ( constructor ) {
			VoidObject tmp;
			ControlFlow::E controlflow = constructor->execute(params, &tmp);

			if ( controlflow != ControlFlow::Normal ) {
				// uups
			}
		}
	}
	else {
		// either the destructor has already been executed
		// or the constructor has never been called successfully!
		//throw Utils::Exceptions::Exception("can not destroy object '" + name() + "' which has not been constructed");
	}

	// set after executing destructor in case any exceptions have been thrown
	mConstructed = false;
}

ControlFlow::E Object::execute(Object *result, const std::string& method, const ParameterList& params, const Method* caller)
{
	OSdebug("execute('" + method + "', [" + toString(params) + "])");

	Method *symbol = static_cast<Method*>(resolveMethod(method, params, true));
	if ( !symbol ) {
		throw Utils::Exceptions::UnknownIdentifer("unknown method '" + method + "' or method with invalid parameter count called!");
	}

	// are we called from a colleague method?
	bool callFromMethod = caller && (caller->resolve(KEYWORD_THIS) == this);

	// check visibility:
	// colleague methods can always call us,
	// for calls from non-member functions the method visibility must be public (or protected if they belong to the same object hierarchy)
	if ( !callFromMethod && symbol->visibility() != Visibility::Public ) {
		throw Utils::Exceptions::VisibilityError("invalid visibility: " + method);
	}

	result->setRepository(mRepository);

	symbol->setOwner(this);
	symbol->setRepository(mRepository);

	// execute our member method
	return symbol->execute(params, result);
}

void Object::garbageCollector()
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		undefine((*it)->getName(), (*it));

		delete (*it);
	}
	mMethods.clear();

	for ( Symbols::reverse_iterator it = mSymbols.rbegin(); it != mSymbols.rend(); ++it ) {
		if ( it->first != KEYWORD_THIS &&
			 it->second && it->second->getType() == Symbol::IType::ObjectSymbol ) {
			// members are objects, so they will get cleaned up by our repository
			mRepository->removeReference(static_cast<Object*>(it->second));
		}
	}
	mSymbols.clear();
}

const std::string& Object::getTypeName() const
{
	return mTypename;
}

std::string Object::getValue() const
{
	return mValue;
}

bool Object::isAtomicType() const
{
	return mIsAtomicType;
}

bool Object::isValid() const
{
	return mConstructed;
}

void Object::operator_assign(Object *other)
{
	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented("operator=: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_bitand(Object *other)
{
	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented("operator&: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_bitor(Object *other)
{
	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented("operator|: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_divide(Object *other)
{
	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented("operator/: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_equal(Object *other)
{
	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented("operator==: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_greater(Object *other)
{
	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented("operator>: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_greater_equal(Object *other)
{
	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented("operator>=: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_less(Object *other)
{
	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented("operator<: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_less_equal(Object *other)
{
	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented("operator<=: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_modulo(Object *other)
{
	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented("operator%: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_multiply(Object *other)
{
	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented("operator*: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_plus(Object *other)
{
	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented("operator+: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_subtract(Object *other)
{
	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented("operator-: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::setRepository(Repository *repository)
{
	mRepository = repository;
}

void Object::setValue(const std::string& value)
{
	mValue = value;
}

std::string Object::ToString() const
{
	std::string result = getName() + " " + Typename() + " = " + getValue();

	if ( !isAtomicType() ) {
		result += " { ";

		for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
			result += (*it)->getTypeName() + " " + (*it)->getName();

			MethodCollection::const_iterator copy = it;
			if ( ++copy != mMethods.end() ) {
				result += ", \n";
			}
		}
		for ( Symbols::const_iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
			if ( !it->second || it->second->getType() != Symbol::IType::ObjectSymbol ) {
				continue;
			}

			result += static_cast<Object*>(it->second)->ToString();

			Symbols::const_iterator copy = it;
			if ( ++copy != mSymbols.end() ) {
				result += ", ";
			}
		}

		result += " }";
	}

	return result;
}


}
}
