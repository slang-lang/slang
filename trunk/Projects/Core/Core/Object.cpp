
// Header
#include "Object.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Repository.h"
#include "System.h"
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
  mThis(0),
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
	mParent = other.mParent;
	mRepository = other.mRepository;
	mTypename = other.mTypename;

	setConst(other.isConst());
	setFinal(other.isFinal());
	setLanguageFeatureState(other.getLanguageFeatureState());
	setMember(other.isMember());
	setValue(other.getValue());

	if ( !mIsAtomicType ) {
		// register this
		define(IDENTIFIER_THIS, this);

		// register new members
		for ( Symbols::const_iterator it = other.mSymbols.begin(); it != other.mSymbols.end(); ++it ) {
			if ( /*it->first == IDENTIFIER_BASE ||*/ it->first == IDENTIFIER_THIS ) {
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

			defineMethod((*it)->getName(), method);
		}
	}

	//mThis = mInheritance.begin()->second;
}

Object::Object(const std::string& name, const std::string& filename, const std::string& type, const std::string& value)
: MethodScope(name, 0),
  ObjectSymbol(name),
  mFilename(filename),
  mIsAtomicType(true),
  mIsConstructed(false),
  mRepository(0),
  mThis(0),
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
		mIsConstructed = other.mIsConstructed;// ? other.mIsConstructed : mIsConstructed;
		mFilename = other.mFilename;
		mParent = other.mParent ? other.mParent : mParent;
		mRepository = other.mRepository ? other.mRepository : mRepository;
		mTypename = other.mTypename;

		setValue(other.getValue());

		garbageCollector();

		if ( !mIsAtomicType ) {
			// register this
			define(IDENTIFIER_THIS, this);

			// register new members
			for ( Symbols::const_iterator it = other.mSymbols.begin(); it != other.mSymbols.end(); ++it ) {
				if ( /*it->first == IDENTIFIER_BASE ||*/ it->first == IDENTIFIER_THIS ) {
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

				defineMethod((*it)->getName(), method);
			}
		}

		//mThis = mInheritance.begin()->second;
	}
}

void Object::addInheritance(const Designtime::Ancestor& ancestor, Object* inheritance)
{
	if ( !inheritance ) {
		// bam!
		throw Utils::Exceptions::Exception("invalid inheritance level added!");
	}

	mInheritance.insert(std::make_pair(ancestor, inheritance));
}

bool Object::CanExecuteDefaultConstructor() const
{
	Symbol* anyConstructor = resolve(Typename(), false);
	if ( !anyConstructor ) {
		// no constructor found at all
		// we can call our default constructor but it won't do anything besides
		// setting our object to constructed
		return true;
	}

	Symbol* defaultConstructor = resolveMethod(Typename(), ParameterList(), true);

	//return !anyConstructor || defaultConstructor;
	return defaultConstructor && (anyConstructor == defaultConstructor);
}

ControlFlow::E Object::Constructor(const ParameterList& params)
{
	ControlFlow::E controlflow = ControlFlow::Normal;

	if ( mIsAtomicType ) {	// hack to initialize atomic types
		if ( !params.empty() ) {
			if ( params.size() != 1 ) {
				throw Utils::Exceptions::ParameterCountMissmatch("atomic types only support one constructor parameter");
			}

			setValue(params.front().value());
		}

		return controlflow;
	}

	if ( mIsConstructed ) {	// prevent multiple instantiations
		throw Utils::Exceptions::Exception("can not construct object '" + getName() + "' multiple times");
	}

	// execute parent object constructors
	for ( Inheritance::iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
/*
		Symbol* anyConstructor = it->second->resolve(Typename(), false);
		Symbol* defaultConstructor = it->second->resolveMethod(Typename(), ParameterList(), true);

		if ( anyConstructor && !defaultConstructor ) {
			break;
		}
*/
		if ( !it->second->CanExecuteDefaultConstructor() ) {
			break;
		}

		// try to execute the default constructor
		controlflow = it->second->Constructor(ParameterList());

		if ( controlflow != ControlFlow::Normal ) {
			return controlflow;
		}
	}

	// check if we have implemented at least one constructor
	Symbol *symbol = resolve(Typename(), true);
	if ( symbol ) {
		// if a specialized constructor is implemented, the default constructor cannot be used

		Method *constructor = static_cast<Method*>(resolveMethod(Typename(), params, true));
		if ( constructor ) {
			VoidObject tmp;
			controlflow = constructor->execute(params, &tmp, TokenIterator());

			if ( controlflow != ControlFlow::Normal ) {
				return controlflow;
			}
		}
		else {
			// no appropriate constructor found
			throw Utils::Exceptions::Exception(Typename() + ": no appropriate constructor found");
		}
	}

/*	// doesn't work properly yes
	// check if all base objects have been constructed correctly
	for ( Inheritance::iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
		if ( !it->second->mIsConstructed ) {
			System::Print("C++ (Constructor): " + getName() + "::" + Typename() + "()");

			throw Utils::Exceptions::Exception(getName() + "::" + Typename() + "(): not all base objects have been instantiated");
		}
	}
*/

	// set after executing constructor in case any exceptions have been thrown
	mIsConstructed = true;

	return controlflow;
}

ControlFlow::E Object::Destructor()
{
	ControlFlow::E controlflow = ControlFlow::Normal;

	if ( mIsConstructed && !mIsAtomicType ) {
		mIsConstructed = false;

		ParameterList params;

		// only execute destructor if one is present
		Method *destructor = static_cast<Method*>(resolveMethod("~" + Typename(), params, true));
		if ( destructor ) {
			VoidObject tmp;
			controlflow = destructor->execute(params, &tmp, TokenIterator());

			if ( controlflow != ControlFlow::Normal ) {
				return controlflow;
			}
		}

		// execute parent object destructors
		for ( Inheritance::iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
			controlflow = it->second->Destructor();

			if ( controlflow != ControlFlow::Normal ) {
				return controlflow;
			}
		}

		garbageCollector();
	}
	else {
		// either the destructor has already been executed
		// or the constructor has never been called successfully!
		//throw Utils::Exceptions::Exception("can not destroy object '" + Typename() + "' which has not been constructed");
	}

	// set after executing destructor in case any exceptions have been thrown
	mIsConstructed = false;

	return controlflow;
}

ControlFlow::E Object::execute(Object *result, const std::string& name, const ParameterList& params, const Method* /*caller*/)
{
	OSdebug("execute('" + name + "', [" + toString(params) + "])");

	if ( !mIsConstructed ) {
		// a method is being called although our object has not yet been constructed?
		throw Utils::Exceptions::AccessViolation("while accessing " + Typename() + "." + name);
	}

	Method *method = static_cast<Method*>(resolveMethod(name, params, false));
	if ( !method ) {
		throw Utils::Exceptions::UnknownIdentifer("unknown method '" + name + "' or method with invalid parameter count called!");
	}

/*
	// are we called from a colleague method?
	bool callFromMethod = caller && (caller->resolve(IDENTIFIER_BASE) == this || caller->resolve(IDENTIFIER_THIS) == this);

	// check visibility:
	// colleague methods can always call us,
	// for calls from non-member functions the method visibility must be public (or protected if they belong to the same object hierarchy)
	if ( !callFromMethod && method->getVisibility() != Visibility::Public ) {
		throw Utils::Exceptions::VisibilityError("invalid visibility: " + name);
	}
*/

	result->setRepository(mRepository);
	method->setRepository(mRepository);

	// execute our member method
	ControlFlow::E controlflow = method->execute(params, result, TokenIterator());

	if ( controlflow == ControlFlow::Normal ) {
		switch ( method->getMethodType() ) {
			case MethodAttributes::MethodType::Constructor:
				assert(!"constructor");
				mIsConstructed = true;
				break;
			case MethodAttributes::MethodType::Destructor:
				assert(!"destructor");
				mIsConstructed = false;
				break;
			default:
				break;
		}
	}

	return controlflow;
}

void Object::garbageCollector()
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		undefine((*it)->getName(), (*it));

		delete (*it);
	}
	mMethods.clear();

	for ( Symbols::reverse_iterator it = mSymbols.rbegin(); it != mSymbols.rend(); ) {
		if ( it->first != IDENTIFIER_BASE && it->first != IDENTIFIER_THIS &&
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

Symbol* Object::resolve(const std::string& name, bool onlyCurrentScope) const
{
	Symbol *result = MethodScope::resolve(name, onlyCurrentScope);

	if ( !result && !onlyCurrentScope ) {
		for ( Inheritance::const_iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
			result = it->second->resolve(name, onlyCurrentScope);

			if ( result ) {
				break;
			}
		}
	}

	return result;
}

ObjectiveScript::MethodSymbol* Object::resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope) const
{
	ObjectiveScript::MethodSymbol *result = 0;

	for ( Inheritance::const_reverse_iterator it = mInheritance.rbegin(); it != mInheritance.rend(); ++it ) {
		ObjectiveScript::MethodSymbol *tmp = it->second->resolveMethod(name, params, onlyCurrentScope);

		if ( tmp && !tmp->isAbstract() && (tmp->getVisibility() == Visibility::Protected || tmp->getVisibility() == Visibility::Public) ) {
			result = tmp;
		}

		if ( result && result->isFinal() ) {
			// we found a method that is not allowed to be overwritten, so this is the one we have to use
			break;
		}
	}

	if ( !result || !result->isFinal() ) {
		ObjectiveScript::MethodSymbol *tmp = MethodScope::resolveMethod(name, params, onlyCurrentScope);

		if ( tmp ) {
			if ( tmp->isAbstract() ) {
				throw Utils::Exceptions::Exception(tmp->getName() + " is abstract");
			}

			result = tmp;
		}
	}

	return result;
}

void Object::setParent(IScope *scope)
{
	mParent = scope;
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
	std::string result = Typename() + " " + getName() + " = " + getValue();

	if ( !isAtomicType() ) {
		result += " { ";

		for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
			result += (*it)->ToString();

			MethodCollection::const_iterator copy = it;
			if ( ++copy != mMethods.end() ) {
				result += ", \n";
			}
		}
		for ( Symbols::const_iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
			if ( it->first == IDENTIFIER_BASE || it->first == IDENTIFIER_THIS ||
				 !it->second || it->second->getType() != Symbol::IType::ObjectSymbol ) {
				continue;
			}

			result += it->second->ToString();

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
