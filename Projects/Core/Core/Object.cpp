
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
  mIsAtomicType(false),
  mIsConstructed(false),
  mRepository(0),
  mThis(0),
  mTypename(ANONYMOUS_OBJECT)
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
	mValue = other.mValue;

	setConst(other.isConst());
	setFinal(other.isFinal());
	setLanguageFeatureState(other.getLanguageFeatureState());
	setMember(other.isMember());

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

Object::Object(const std::string& name, const std::string& filename, const std::string& type, AtomicValue value)
: MethodScope(name, 0),
  ObjectSymbol(name),
  mFilename(filename),
  mIsAtomicType(false),
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
		mIsAtomicType = other.mIsAtomicType;
		mIsConstructed = other.mIsConstructed;// ? other.mIsConstructed : mIsConstructed;
		mFilename = other.mFilename;
		mParent = other.mParent ? other.mParent : mParent;
		mRepository = other.mRepository ? other.mRepository : mRepository;
		mTypename = other.mTypename;
		mValue = other.mValue;

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
			controlflow = constructor->execute(params, &tmp, Token());

			if ( controlflow != ControlFlow::Normal ) {
				return controlflow;
			}
		}
		else {
			// no appropriate constructor found
			throw Utils::Exceptions::Exception(Typename() + ": no appropriate constructor found");
		}
	}

/*	// doesn't work properly yet
	// check if all base objects have been constructed correctly
	for ( Inheritance::iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
		if ( !it->second->mIsConstructed ) {
			System::Print("C++ (Constructor): " + getName() + "::" + Typename() + "()");

			throw Utils::Exceptions::Exception(getName() + "::" + Typename() + "(): not all base objects have been constructed correctly");
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
			controlflow = destructor->execute(params, &tmp, Token());

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

	ControlFlow::E controlflow = ControlFlow::Normal;

	if ( !mIsConstructed ) {
		// a method is being called although our object has not yet been constructed?
		return ControlFlow::Throw;
	}

	Method *method = static_cast<Method*>(resolveMethod(name, params, false));
	if ( !method ) {
		throw Utils::Exceptions::UnknownIdentifer("unknown method '" + getName() + "." + name + "' or method with invalid parameter count called!");
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
	controlflow = method->execute(params, result, Token());

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

bool Object::FromJson(const Json::Value& value)
{
	for ( Json::Value::Members::const_iterator it = value.members().begin(); it != value.members().end(); ++it ) {
		Json::Value sub = (*it);

		Symbol *symbol = resolve(sub.key(), true);
		if ( !symbol ) {
			throw Utils::Exceptions::Exception("FromJson: unknown member '" + sub.key() + "'!");
		}

		Object *obj = static_cast<Object*>(symbol);
		if ( obj->isAtomicType() ) {
			obj->setValue(sub.asString().c_str());
		}
		else {
			obj->FromJson(sub);
		}
	}

	return true;
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

AtomicValue Object::getValue() const
{
	return mValue;
}

bool Object::isAtomicType() const
{
	return mIsAtomicType;
}

bool Object::isValid() const
{
	return mIsConstructed;
}

void Object::operator_assign(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(ANONYMOUS_OBJECT, Typename(), VALUE_NONE)
		//Parameter(ANONYMOUS_OBJECT, Typename(), other->getValue(), false, false, Parameter::AccessMode::ByValue, other)
	);

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("=operator", params, true);
	if ( value_operator ) {
		Object tmp;
		static_cast<Method*>(value_operator)->execute(params, &tmp, Token());

		operator_assign(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented(Typename() + ".operator=: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_bitand(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(ANONYMOUS_OBJECT, Typename(), VALUE_NONE)
		//Parameter(ANONYMOUS_OBJECT, Typename(), other->getValue(), false, false, Parameter::AccessMode::ByValue, other)
	);

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("&operator", params, true);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, true);
	}
	if ( value_operator ) {
		Object tmp;
		static_cast<Method*>(value_operator)->execute(params, &tmp, Token());

		operator_bitand(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented(Typename() + ".operator&: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_bitcomplement(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(ANONYMOUS_OBJECT, Typename(), VALUE_NONE)
		//Parameter(ANONYMOUS_OBJECT, Typename(), other->getValue(), false, false, Parameter::AccessMode::ByValue, other)
	);

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("~operator", params, true);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, true);
	}
	if ( value_operator ) {
		Object tmp;
		static_cast<Method*>(value_operator)->execute(params, &tmp, Token());

		operator_bitcomplement(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented(Typename() + ".operator~: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_bitor(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(ANONYMOUS_OBJECT, Typename(), VALUE_NONE)
		//Parameter(ANONYMOUS_OBJECT, Typename(), other->getValue(), false, false, Parameter::AccessMode::ByValue, other)
	);

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("|operator", params, true);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, true);
	}
	if ( value_operator ) {
		Object tmp;
		static_cast<Method*>(value_operator)->execute(params, &tmp, Token());

		operator_bitor(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented(Typename() + ".operator|: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_bool() const
{
	throw Utils::Exceptions::NotImplemented(Typename() + ".operator bool(): for " + Typename() + " not supported");
}

void Object::operator_divide(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(ANONYMOUS_OBJECT, Typename(), VALUE_NONE)
		//Parameter(ANONYMOUS_OBJECT, Typename(), other->getValue(), false, false, Parameter::AccessMode::ByValue, other)
	);

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("/operator", params, true);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, true);
	}
	if ( value_operator ) {
		Object tmp;
		static_cast<Method*>(value_operator)->execute(params, &tmp, Token());

		operator_divide(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented(Typename() + ".operator/: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_equal(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(ANONYMOUS_OBJECT, Typename(), VALUE_NONE)
		//Parameter(ANONYMOUS_OBJECT, Typename(), other->getValue(), false, false, Parameter::AccessMode::ByValue, other)
	);

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("==operator", params, true);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, true);
	}
	if ( value_operator ) {
		Object tmp;
		static_cast<Method*>(value_operator)->execute(params, &tmp, Token());

		return operator_equal(&tmp);
	}

	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented(Typename() + ".operator==: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_greater(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(ANONYMOUS_OBJECT, Typename(), VALUE_NONE)
		//Parameter(ANONYMOUS_OBJECT, Typename(), other->getValue(), false, false, Parameter::AccessMode::ByValue, other)
	);

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod(">operator", params, true);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, true);
	}
	if ( value_operator ) {
		Object tmp;
		static_cast<Method*>(value_operator)->execute(params, &tmp, Token());

		return operator_greater(&tmp);
	}

	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented(Typename() + ".operator>: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_greater_equal(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(ANONYMOUS_OBJECT, Typename(), VALUE_NONE)
		//Parameter(ANONYMOUS_OBJECT, Typename(), other->getValue(), false, false, Parameter::AccessMode::ByValue, other)
	);

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod(">=operator", params, true);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, true);
	}
	if ( value_operator ) {
		Object tmp;
		static_cast<Method*>(value_operator)->execute(params, &tmp, Token());

		return operator_greater_equal(&tmp);
	}

	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented(Typename() + ".operator>=: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_less(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(ANONYMOUS_OBJECT, Typename(), VALUE_NONE)
		//Parameter(ANONYMOUS_OBJECT, Typename(), other->getValue(), false, false, Parameter::AccessMode::ByValue, other)
	);

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("<operator", params, true);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, true);
	}
	if ( value_operator ) {
		Object tmp;
		static_cast<Method*>(value_operator)->execute(params, &tmp, Token());

		return operator_less(&tmp);
	}

	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented(Typename() + ".operator<: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_less_equal(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(ANONYMOUS_OBJECT, Typename(), VALUE_NONE)
		//Parameter(ANONYMOUS_OBJECT, Typename(), other->getValue(), false, false, Parameter::AccessMode::ByValue, other)
	);

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("<=operator", params, true);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, true);
	}
	if ( value_operator ) {
		Object tmp;
		static_cast<Method*>(value_operator)->execute(params, &tmp, Token());

		return operator_less_equal(&tmp);
	}

	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented(Typename() + ".operator<=: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_modulo(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(ANONYMOUS_OBJECT, Typename(), VALUE_NONE)
		//Parameter(ANONYMOUS_OBJECT, Typename(), other->getValue(), false, false, Parameter::AccessMode::ByValue, other)
	);

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("%operator", params, true);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, true);
	}
	if ( value_operator ) {
		Object tmp;
		static_cast<Method*>(value_operator)->execute(params, &tmp, Token());

		operator_modulo(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented(Typename() + ".operator%: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_multiply(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(ANONYMOUS_OBJECT, Typename(), VALUE_NONE)
		//Parameter(ANONYMOUS_OBJECT, Typename(), other->getValue(), false, false, Parameter::AccessMode::ByValue, other)
	);

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("*operator", params, true);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, true);
	}
	if ( value_operator ) {
		Object tmp;
		static_cast<Method*>(value_operator)->execute(params, &tmp, Token());

		operator_multiply(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented(Typename() + ".operator*: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_plus(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(ANONYMOUS_OBJECT, Typename(), VALUE_NONE)
		//Parameter(ANONYMOUS_OBJECT, Typename(), other->getValue(), false, false, Parameter::AccessMode::ByValue, other)
	);

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("+operator", params, true);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, true);
	}
	if ( value_operator ) {
		Object tmp;
		static_cast<Method*>(value_operator)->execute(params, &tmp, Token());

		operator_plus(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented(Typename() + ".operator+: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_subtract(const Object *other)
{
	ParameterList params;
	params.push_back(
		Parameter(ANONYMOUS_OBJECT, Typename(), VALUE_NONE)
		//Parameter(ANONYMOUS_OBJECT, Typename(), other->getValue(), false, false, Parameter::AccessMode::ByValue, other)
	);

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("-operator", params, true);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, true);
	}
	if ( value_operator ) {
		Object tmp;
		static_cast<Method*>(value_operator)->execute(params, &tmp, Token());

		operator_subtract(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Utils::Exceptions::NotImplemented(Typename() + ".operator-: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_unary_decrement()
{
	throw Utils::Exceptions::NotImplemented(Typename() + ".operator--: for " + Typename() + " not supported");
}

void Object::operator_unary_increment()
{
	throw Utils::Exceptions::NotImplemented(Typename() + ".operator++: for " + Typename() + " not supported");
}

void Object::operator_unary_minus()
{
	throw Utils::Exceptions::NotImplemented(Typename() + ".operator unary -: for " + Typename() + " not supported");
}

void Object::operator_unary_not()
{
	throw Utils::Exceptions::NotImplemented(Typename() + ".operator unary !: for " + Typename() + " not supported");
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

		if ( tmp && (tmp->getVisibility() == Visibility::Protected || tmp->getVisibility() == Visibility::Public) ) {
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

void Object::setValue(AtomicValue value)
{
	mValue = value;
}

Json::Value Object::ToJson() const
{
	Json::Value result;

	for ( Symbols::const_iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
		if ( it->first == IDENTIFIER_BASE ) {
			result.addMember(it->first, static_cast<Object*>(it->second)->ToJson());
		}

		if ( it->first == IDENTIFIER_BASE || it->first == IDENTIFIER_THIS ||
			 !it->second || it->second->getType() != Symbol::IType::ObjectSymbol ) {
			continue;
		}

		Object *obj = static_cast<Object*>(it->second);

		result.addMember(it->first, obj->getValue().toStdString());
	}

	return result;
}

std::string Object::ToString() const
{
	std::string result = Typename() + " " + getName();

	if ( isAtomicType() ) {
		result += " = " + getValue().toStdString();
	}
	else {
		result += " {\n";

		for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
			result += "\t" + (*it)->ToString() + "\n";
		}

		result += "\n";

		for ( Symbols::const_iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
			if ( it->first == IDENTIFIER_BASE || it->first == IDENTIFIER_THIS ||
				 !it->second || it->second->getType() != Symbol::IType::ObjectSymbol ) {
				continue;
			}

			result += "\t" + it->second->ToString() + "\n";
		}

		result += "}";
	}

	return result;
}


}
}
