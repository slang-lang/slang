
// Header
#include "Object.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Repository.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


Object::Object()
: MethodScope(ANONYMOUS_OBJECT, 0),
  ObjectSymbol(ANONYMOUS_OBJECT),
  mFilename(ANONYMOUS_OBJECT),
  mIsAtomicType(true),
  mIsConstructed(false),
  mRepository(0),
  mTypename(ANONYMOUS_OBJECT),
  mValue(VALUE_NONE)
{
}

Object::Object(const Object& other)
: MethodScope(other.getName(), 0),
  ObjectSymbol(other.getName())
{
	mFilename = other.mFilename;
	mIsAtomicType = other.mIsAtomicType;
	mIsConstructed = other.mIsConstructed;
	mRepository = other.mRepository;
	mTypename = other.mTypename;

	setConst(other.isConst());
	setFinal(other.isFinal());
	setLanguageFeatureState(other.getLanguageFeatureState());
	setMember(other.isMember());
	setValue(other.getValue());

	if ( !mIsAtomicType ) {
		// register this
		define(KEYWORD_THIS, this);

		// register new members
		for ( Symbols::const_iterator it = other.mSymbols.begin(); it != other.mSymbols.end(); ++it ) {
			if ( it->first == KEYWORD_THIS ) {
				continue;
			}

			if ( it->second && it->second->getType() == Symbol::IType::ObjectSymbol ) {
				mRepository->addReference(static_cast<Object*>(it->second));
			}

			define(it->first, it->second);
		}

		// register new methods
		for ( MethodCollection::const_iterator it = other.mMethods.begin(); it != other.mMethods.end(); ++it ) {
			Method *method = new Method(this, (*it)->getName(), (*it)->Typename());
			*method = *(*it);

			defineMethod(method);
		}
	}
}

Object::Object(const std::string& name, const std::string& filename, const std::string& type, const std::string& value)
: MethodScope(name, 0),
  ObjectSymbol(name),
  mFilename(filename),
  mIsAtomicType(true),
  mIsConstructed(false),
  mRepository(0),
  mTypename(type),
  mValue(value)
{
}

Object::~Object()
{
	garbageCollector();
}

void Object::operator= (const Object& other)
{
	if ( this != &other ) {
		if ( !mRepository ) {
			mRepository = other.mRepository;
		}

		mIsAtomicType = other.mIsAtomicType;
		mIsConstructed = other.mIsConstructed ? other.mIsConstructed : mIsConstructed;
		mFilename = other.mFilename;
		mTypename = other.mTypename;

		setValue(other.getValue());

		garbageCollector();

		if ( !mIsAtomicType ) {
			// register this
			define(KEYWORD_THIS, this);

			// register new members
			for ( Symbols::const_iterator it = other.mSymbols.begin(); it != other.mSymbols.end(); ++it ) {
				if ( it->first == KEYWORD_THIS ) {
					continue;
				}

				if ( it->second && it->second->getType() == Symbol::IType::ObjectSymbol ) {
					mRepository->addReference(static_cast<Object*>(it->second));
				}

				define(it->first, it->second);
			}

			// register new methods
			for ( MethodCollection::const_iterator it = other.mMethods.begin(); it != other.mMethods.end(); ++it ) {
				Method *method = new Method(this, (*it)->getName(), (*it)->Typename());
				*method = *(*it);

				defineMethod(method);
			}
		}
	}
}

void Object::Constructor(const ParameterList& params)
{
	// hack to initialize atomic types
	if ( isAtomicType() && !params.empty() ) {
		if ( params.size() != 1 ) {
			throw Utils::Exceptions::ParameterCountMissmatch("atomic types only support one constructor parameter");
		}

		mValue = params.front().value();
		return;
	}

	if ( mIsConstructed ) {
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
	mIsConstructed = true;
}

void Object::Destructor()
{
	if ( mIsConstructed ) {
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
	mIsConstructed = false;
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
	if ( !callFromMethod && symbol->getVisibility() != Visibility::Public ) {
		throw Utils::Exceptions::VisibilityError("invalid visibility: " + method);
	}

	result->setRepository(mRepository);
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

	for ( Symbols::reverse_iterator it = mSymbols.rbegin(); it != mSymbols.rend(); ) {
		if ( it->first != KEYWORD_THIS &&
			 it->second && it->second->getType() == Symbol::IType::ObjectSymbol ) {
			mRepository->removeReference(static_cast<Object*>(it->second));
		}

		undefine(it->first, it->second);
	}
	mSymbols.clear();
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
	if ( !mIsAtomicType ) {
		return mIsConstructed;
	}

	//return getValue() == "0" || getValue() == "0.0" || getValue() == FALSE;
	return mIsConstructed;
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

void Object::operator_bitcomplement(Object *other)
{
	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented("operator~: conversion from " + target + " to " + Typename() + " not supported");
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

void Object::operator_unary_decrement()
{
	throw Utils::Exceptions::NotImplemented("operator--: for " + Typename() + " not supported");
}

void Object::operator_unary_increment()
{
	throw Utils::Exceptions::NotImplemented("operator++: for " + Typename() + " not supported");
}

void Object::operator_unary_minus()
{
	throw Utils::Exceptions::NotImplemented("operator unary -: for " + Typename() + " not supported");
}

void Object::operator_unary_not()
{
	throw Utils::Exceptions::NotImplemented("operator unary !: for " + Typename() + " not supported");
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
	std::string result = getName() + /*" " + Typename()*/ + " = " + getValue();

	if ( !isAtomicType() ) {
		result += " { ";

		for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
			result += (*it)->Typename() + " " + (*it)->getName();

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
