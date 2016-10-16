
// Header
#include "Object.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/VirtualMachine/Controller.h>
#include <Tools/Strings.h>
#include <Utils.h>
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


Object::Object()
: MethodScope(ANONYMOUS_OBJECT, 0),
  ObjectSymbol(ANONYMOUS_OBJECT),
  mFilename(ANONYMOUS_OBJECT),
  mIsArray(false),
  mIsArrayDynamicallyExpanding(false),
  mIsAtomicType(false),
  mIsConstructed(false),
  mOutterface(ANONYMOUS_OBJECT),
  mQualifiedOutterface(ANONYMOUS_OBJECT),
  mQualifiedTypename(ANONYMOUS_OBJECT),
  mTypename(ANONYMOUS_OBJECT),
  mBase(0),
  mThis(this)
{
}

Object::Object(const Object& other)
: MethodScope(other.getName(), other.mParent),
  ObjectSymbol(other.getName()),
  mBase(0),
  mThis(this)
{
	mFilename = other.mFilename;
	mInheritance = other.mInheritance;
	mIsArray = other.mIsArray;
	mIsArrayDynamicallyExpanding = other.mIsArrayDynamicallyExpanding;
	mIsAtomicType = other.mIsAtomicType;
	mIsConstructed = other.mIsConstructed;
	mParent = other.mParent;
	mScopeName = other.mScopeName;
	mScopeType = other.mScopeType;
	mValue = other.mValue;

	//if ( other.mQualifiedOutterface != NULL_TYPE ) {
		mOutterface = other.mOutterface;
		mQualifiedOutterface = other.mQualifiedOutterface;
		mQualifiedTypename = other.mQualifiedTypename;
		mTypename = other.mTypename;
	//}

	setConst(other.isConst());
	setFinal(other.isFinal());
	setLanguageFeatureState(other.getLanguageFeatureState());
	setMember(other.isMember());

	assignReference(other.mReference);
}

Object::Object(const std::string& name, const std::string& filename, const std::string& type, AtomicValue value)
: MethodScope(name, 0),
  ObjectSymbol(name),
  mFilename(filename),
  mIsArray(false),
  mIsArrayDynamicallyExpanding(false),
  mIsAtomicType(false),
  mIsConstructed(false),
  mOutterface(type),
  mQualifiedOutterface(type),
  mQualifiedTypename(type),
  mTypename(type),
  mValue(value),
  mBase(0),
  mThis(this)
{
}

Object::~Object()
{
	if ( mReference.isValid() ) {
		Controller::Instance().memory()->remove(mReference);
	}
	else {
		Object* base = dynamic_cast<Object*>(resolve("base", true));
		if ( base ) {
			Controller::Instance().memory()->remove(base->mReference);
		}
	}
}

void Object::operator= (const Object& other)
{
	if ( this != &other ) {
		mFilename = other.mFilename;
		mInheritance = other.mInheritance;
		mIsArray = other.mIsArray;
		mIsArrayDynamicallyExpanding = other.mIsArrayDynamicallyExpanding;
		mIsAtomicType = other.mIsAtomicType;
		mIsConstructed = other.mIsConstructed;// ? other.mIsConstructed : mIsConstructed;
		mParent = other.mParent ? other.mParent : mParent;
		mScopeName = other.mScopeName;
		mScopeType = other.mScopeType;
		mValue = other.mValue;

		if ( mQualifiedOutterface == NULL_TYPE ) {
			mOutterface = other.mOutterface;
			mQualifiedOutterface = other.mQualifiedOutterface;
		}
		mQualifiedTypename = other.mQualifiedTypename;
		mTypename = other.mTypename;

		assignReference(other.mReference);
	}
}

void Object::assign(const Object& other, bool overrideType)
{
	if ( this != &other ) {
		mFilename = other.mFilename;
		mInheritance = other.mInheritance;
		mIsArray = other.mIsArray;
		mIsArrayDynamicallyExpanding = other.mIsArrayDynamicallyExpanding;
		mIsAtomicType = other.mIsAtomicType;
		mIsConstructed = other.mIsConstructed;// ? other.mIsConstructed : mIsConstructed;
		mParent = other.mParent ? other.mParent : mParent;
		mScopeName = other.mScopeName;
		mScopeType = other.mScopeType;
		mValue = other.mValue;

		if ( mQualifiedOutterface == NULL_TYPE || overrideType ) {
			mOutterface = other.mOutterface;
			mQualifiedOutterface = other.mQualifiedOutterface;
		}
		mQualifiedTypename = other.mQualifiedTypename;
		mTypename = other.mTypename;

		assignReference(other.mReference);
	}
}

void Object::assignReference(const Reference& ref)
{
	if ( !ref.isValid() ) {
		mThis = this;
		mBase = 0;
	}
	else {
		Controller::Instance().memory()->add(ref);
		mReference = ref;

		mThis = Controller::Instance().memory()->get(ref);
		mBase = dynamic_cast<Object*>(mThis->resolve("base", true));
	}
}

void Object::copy(const Object& other)
{
	if ( this != &other ) {
		mFilename = other.mFilename;
		mInheritance = other.mInheritance;
		mIsArray = other.mIsArray;
		mIsArrayDynamicallyExpanding = other.mIsArrayDynamicallyExpanding;
		mIsAtomicType = other.mIsAtomicType;
		mIsConstructed = other.mIsConstructed;// ? other.mIsConstructed : mIsConstructed;
		mFilename = other.mFilename;
		mOutterface = other.mTypename;
		mParent = other.mParent ? other.mParent : mParent;
		mQualifiedOutterface = other.mQualifiedTypename;
		mQualifiedTypename = other.mQualifiedTypename;
		mScopeName = other.mScopeName;
		mScopeType = other.mScopeType;
		mTypename = other.mTypename;
		mValue = other.mValue;

		garbageCollector();

		if ( !mIsAtomicType ) {
			// register this
			define(IDENTIFIER_THIS, this);

			// register new members
			for ( Symbols::const_iterator it = other.mSymbols.begin(); it != other.mSymbols.end(); ++it ) {
				if ( /*it->first == IDENTIFIER_BASE ||*/
					it->first == IDENTIFIER_THIS ||
					!it->second || it->second->getSymbolType() != Symbol::IType::ObjectSymbol) {
					continue;
				}

				Object* source = static_cast<Object*>(it->second);
				Object* target = Controller::Instance().repository()->createInstance(source->Typename(), source->getName(), false);
				target->copy(*source);

				define(target->getName(), target);
			}

			// register new methods
			for ( MethodCollection::const_iterator it = other.mMethods.begin(); it != other.mMethods.end(); ++it ) {
				Method *method = new Method(this, (*it)->getName(), (*it)->Typename());
				*method = *(*it);

				defineMethod((*it)->getName(), method);
			}
		}
	}
}

void Object::addInheritance(const Designtime::Ancestor& ancestor, Object* inheritance)
{
	if ( !inheritance ) {
		// bam!
		throw Common::Exceptions::Exception("invalid inheritance level added!");
	}

	mInheritance.insert(std::make_pair(ancestor, inheritance));
}

bool Object::CanExecuteDefaultConstructor() const
{
	Symbol* anyConstructor = resolve(Typename(), false);
	if ( !anyConstructor ) {
		// no constructor found at all, so we can call our default constructor but it won't do anything besides setting our object to constructed
		return true;
	}

	Symbol* defaultConstructor = resolveMethod(Typename(), ParameterList(), true);

	return defaultConstructor && (anyConstructor == defaultConstructor);
}

ControlFlow::E Object::Constructor(const ParameterList& params)
{
	ControlFlow::E controlflow = ControlFlow::Normal;

	if ( mIsAtomicType ) {	// hack to initialize atomic types
		if ( !params.empty() ) {
			if ( params.size() != 1 ) {
				throw Common::Exceptions::ParameterCountMissmatch("atomic types only support one constructor parameter");
			}

			setValue(params.front().value());
		}

		return controlflow;
	}

	if ( mIsConstructed ) {	// prevent multiple instantiations
		throw Common::Exceptions::Exception("can not construct object '" + getFullScopeName() + "' multiple times");
	}

	// execute parent object constructors
	for ( Inheritance::iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
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
	Symbol *symbol = 0;
	if ( mReference.isValid() ) {
		symbol = Controller::Instance().memory()->get(mReference)->resolve(Typename(), true);
	}
	else {
		symbol = resolve(Typename(), true);
	}

	if ( symbol ) {
		// if a specialized constructor is implemented, the default constructor cannot be used
/*
		Method *constructor = 0;
		if ( mReference.isValid() ) {
			constructor = dynamic_cast<Method*>(Controller::Instance().memory()->get(mReference)->resolveMethod(Typename(), params, true));
		}
		else {
			constructor = dynamic_cast<Method*>(resolveMethod(Typename(), params, true));
		}
*/

		Method *constructor = dynamic_cast<Method*>(resolveMethod(Typename(), params, true));
		if ( constructor ) {
			VoidObject tmp;

			Interpreter interpreter;
			controlflow = interpreter.execute(constructor, params, &tmp);

			if ( controlflow != ControlFlow::Normal ) {
				return controlflow;
			}
		}
		else {
			// no appropriate constructor found
			throw Common::Exceptions::Exception(Typename() + ": no appropriate constructor found");
		}
	}

/*	// doesn't work properly yet
	// check if all base objects have been constructed correctly
	for ( Inheritance::iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
		if ( !it->second->mIsConstructed ) {
			System::Print("C++ (Constructor): " + getName() + "::" + Typename() + "()");

			throw Common::Exceptions::Exception(getName() + "::" + Typename() + "(): not all base objects have been constructed correctly");
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
			//controlflow = destructor->execute(params, &tmp, Token());

			Interpreter interpreter;
			controlflow = interpreter.execute(destructor, params, &tmp);

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
		//throw Common::Exceptions::Exception("can not destroy object '" + Typename() + "' which has not been constructed");
	}

	// set after executing destructor in case any exceptions have been thrown
	mIsConstructed = false;

	return controlflow;
}

ControlFlow::E Object::execute(Object *result, const std::string& name, const ParameterList& params, const Method* /*caller*/)
{
	if ( !mIsConstructed ) {
		// a method is being called although our object has not yet been constructed?
		throw Runtime::Exceptions::NullPointerException("executed method '" + name + "' of uninitialized object '" + QualifiedTypename() + "'");
	}

	Method *method = static_cast<Method*>(resolveMethod(name, params, false));
	if ( !method ) {
		throw Common::Exceptions::UnknownIdentifer("unknown method '" + getFullScopeName() + "." + name + "' or method with invalid parameter count called!");
	}

/*
	// are we called from a colleague method?
	bool callFromMethod = caller && (caller->resolve(IDENTIFIER_BASE) == this || caller->resolve(IDENTIFIER_THIS) == this);

	// check visibility:
	// colleague methods can always call us,
	// for calls from non-member functions the method visibility must be public (or protected if they belong to the same object hierarchy)
	if ( !callFromMethod && method->getVisibility() != Visibility::Public ) {
		throw Common::Exceptions::VisibilityError("invalid visibility: " + name);
	}
*/

	Interpreter interpreter;

	// execute our member method
	return interpreter.execute(method, params, result);
}

bool Object::FromJson(const Json::Value& value)
{
	for ( Json::Value::Members::const_iterator it = value.members().begin(); it != value.members().end(); ++it ) {
		Json::Value sub = (*it);

		Symbol *symbol = resolve(sub.key(), true);
		if ( !symbol ) {
			throw Common::Exceptions::Exception("FromJson: unknown member '" + sub.key() + "'!");
		}

		Object *obj = static_cast<Object*>(symbol);
		if ( obj->isAtomicType() ) {
			obj->setValue(sub.asString());
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

	Symbols tmp = mSymbols;

	for ( Symbols::iterator symIt = tmp.begin(); symIt != tmp.end(); ++symIt) {
		if ( symIt->first != IDENTIFIER_BASE &&
			 symIt->first != IDENTIFIER_THIS &&
			 symIt->second && symIt->second->getSymbolType() == Symbol::IType::ObjectSymbol ) {
			delete symIt->second;
		}

		mSymbols.erase(symIt->first);
	}
}

AtomicValue Object::getValue() const
{
	return mValue;
}

bool Object::isArray() const
{
	return mIsArray;
}

bool Object::isAbstract() const
{
	bool result = false;

	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( (*it)->isAbstract() ) {
			result = true;
		}
	}

	return result || getImplementationType() == ImplementationType::Abstract || getImplementationType() == ImplementationType::Interface;
}

bool Object::isAtomicType() const
{
	return mIsAtomicType;
}

bool Object::isInstanceOf(const std::string& type) const
{
	if ( type.empty() ) {
		return false;
	}

	if ( QualifiedTypename() == type ) {
		return true;
	}

	for ( Inheritance::const_iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
		if ( it->second->isInstanceOf(type) ) {
			return true;
		}
	}

	return false;
}

bool Object::isValid() const
{
	return mIsConstructed;
}

const Object* Object::operator_array(const Object *index)
{
	if ( !mIsArray ) {
		throw Common::Exceptions::Exception(Typename() + ".operator[]: is not an array");
	}

	std::string subscript = index->Typename();

	throw Common::Exceptions::NotImplemented(Typename() + ".operator[]: no array subscript operator for " + subscript + " implemented");
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

		Interpreter interpreter;
		interpreter.execute(static_cast<Method*>(value_operator), params, &tmp);

		operator_assign(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Common::Exceptions::NotImplemented(Typename() + ".operator=: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_bitand(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator&: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

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

		Interpreter interpreter;
		interpreter.execute(static_cast<Method*>(value_operator), params, &tmp);

		operator_bitand(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Common::Exceptions::NotImplemented(Typename() + ".operator&: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_bitcomplement(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator~: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

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

		Interpreter interpreter;
		interpreter.execute(static_cast<Method*>(value_operator), params, &tmp);

		operator_bitcomplement(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Common::Exceptions::NotImplemented(Typename() + ".operator~: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_bitor(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator|: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

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

		Interpreter interpreter;
		interpreter.execute(static_cast<Method*>(value_operator), params, &tmp);

		operator_bitor(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Common::Exceptions::NotImplemented(Typename() + ".operator|: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_bool() const
{
	throw Common::Exceptions::NotImplemented(Typename() + ".operator bool(): for " + Typename() + " not supported");
}

void Object::operator_divide(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator/: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

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

		Interpreter interpreter;
		interpreter.execute(static_cast<Method*>(value_operator), params, &tmp);

		operator_divide(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Common::Exceptions::NotImplemented(Typename() + ".operator/: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_equal(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator==: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

	if ( mReference.isValid() && other->mReference.isValid() ) {
		return mReference == other->mReference;
	}

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

		Interpreter interpreter;
		interpreter.execute(static_cast<Method*>(value_operator), params, &tmp);

		return operator_equal(&tmp);
	}

	std::string target = other->Typename();

	throw Common::Exceptions::NotImplemented(Typename() + ".operator==: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_greater(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

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

		Interpreter interpreter;
		interpreter.execute(static_cast<Method*>(value_operator), params, &tmp);

		return operator_greater(&tmp);
	}

	std::string target = other->Typename();

	throw Common::Exceptions::NotImplemented(Typename() + ".operator>: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_greater_equal(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

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

		Interpreter interpreter;
		interpreter.execute(static_cast<Method*>(value_operator), params, &tmp);

		return operator_greater_equal(&tmp);
	}

	std::string target = other->Typename();

	throw Common::Exceptions::NotImplemented(Typename() + ".operator>=: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_is(const Symbol *other)
{
	if ( !other || other->getSymbolType() != Symbol::IType::BluePrintObjectSymbol ) {
		throw Common::Exceptions::Exception("invalid symbol provided");
	}

	return isInstanceOf(static_cast<const Designtime::BluePrintObject*>(other)->QualifiedTypename());
}

bool Object::operator_less(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

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

		Interpreter interpreter;
		interpreter.execute(static_cast<Method*>(value_operator), params, &tmp);

		return operator_less(&tmp);
	}

	std::string target = other->Typename();

	throw Common::Exceptions::NotImplemented(Typename() + ".operator<: conversion from " + target + " to " + Typename() + " not supported");
}

bool Object::operator_less_equal(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

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

		Interpreter interpreter;
		interpreter.execute(static_cast<Method*>(value_operator), params, &tmp);

		return operator_less_equal(&tmp);
	}

	std::string target = other->Typename();

	throw Common::Exceptions::NotImplemented(Typename() + ".operator<=: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_modulo(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator%: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

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

		Interpreter interpreter;
		interpreter.execute(static_cast<Method*>(value_operator), params, &tmp);

		operator_modulo(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Common::Exceptions::NotImplemented(Typename() + ".operator%: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_multiply(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator*: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

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

		Interpreter interpreter;
		interpreter.execute(static_cast<Method*>(value_operator), params, &tmp);

		operator_multiply(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Common::Exceptions::NotImplemented(Typename() + ".operator*: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_plus(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator+: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

	ParameterList params;
	params.push_back(
		Parameter(ANONYMOUS_OBJECT, QualifiedTypename(), VALUE_NONE)
		//Parameter(ANONYMOUS_OBJECT, Typename(), other->getValue(), false, false, Parameter::AccessMode::ByValue, other)
	);

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("+operator", params, true);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, true);
	}
	if ( value_operator ) {
		Object tmp;

		Interpreter interpreter;
		interpreter.execute(static_cast<Method*>(value_operator), params, &tmp);

		operator_plus(&tmp);
		return;
	}

	throw Common::Exceptions::NotImplemented(QualifiedTypename() + ".operator+: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_subtract(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator-: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

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

		Interpreter interpreter;
		interpreter.execute(static_cast<Method*>(value_operator), params, &tmp);

		operator_subtract(&tmp);
		return;
	}

	std::string target = other->Typename();

	throw Common::Exceptions::NotImplemented(Typename() + ".operator-: conversion from " + target + " to " + Typename() + " not supported");
}

void Object::operator_unary_decrement()
{
	throw Common::Exceptions::NotImplemented(Typename() + ".operator--: for " + Typename() + " not supported");
}

void Object::operator_unary_increment()
{
	throw Common::Exceptions::NotImplemented(Typename() + ".operator++: for " + Typename() + " not supported");
}

void Object::operator_unary_minus()
{
	throw Common::Exceptions::NotImplemented(Typename() + ".operator unary -: for " + Typename() + " not supported");
}

void Object::operator_unary_not()
{
	throw Common::Exceptions::NotImplemented(Typename() + ".operator unary !: for " + Typename() + " not supported");
}

Symbol* Object::resolve(const std::string& name, bool onlyCurrentScope) const
{
	if ( mThis != this ) {
		return mThis->resolve(name, true);
	}

	// (1) look only in current scope
	Symbol *result = MethodScope::resolve(name, true);

	// (2) check inheritance
	if ( !result ) {
		if ( mBase && !onlyCurrentScope ) {
			result = mBase->resolve(name, onlyCurrentScope);
		}
	}

	// (3) if we still haven't found something also look in other scopes
	if ( !result && !onlyCurrentScope ) {
		result = MethodScope::resolve(name, false);
	}

	return result;
}

ObjectiveScript::MethodSymbol* Object::resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope) const
{
	if ( mThis != this ) {
		return mThis->resolveMethod(name, params, true);
	}

	// (1) look in current scope
	ObjectiveScript::MethodSymbol *result = MethodScope::resolveMethod(name, params, true);

	// (2) check inheritance
	// we cannot go the short is-result-already-set way here because one of our ancestor methods could be marked as final
	if ( mBase && !onlyCurrentScope ) {
		result = mBase->resolveMethod(name, params, onlyCurrentScope);
	}

	// (3) if we still haven't found something also look in other scopes
	if ( !result || !result->isFinal() ) {
		if ( !onlyCurrentScope ) {
			ObjectiveScript::MethodSymbol *tmp = MethodScope::resolveMethod(name, params, false);

			if ( tmp ) {
				result = tmp;
			}
		}
	}

	return result;
}

void Object::setArray(bool value, size_t size)
{
	mIsArray = value;
	mIsArrayDynamicallyExpanding = (size == 0);
}

void Object::setConstructed(bool state)
{
	mIsConstructed = state;
}

void Object::setParent(IScope *scope)
{
	mParent = scope;
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
			 !it->second || it->second->getSymbolType() != Symbol::IType::ObjectSymbol ) {
			continue;
		}

		Object *obj = static_cast<Object*>(it->second);

		result.addMember(it->first, obj->getValue().toStdString());
	}

	return result;
}

std::string Object::ToString(unsigned int indent) const
{
	std::string result;
	result += ::Utils::Tools::indent(indent);
	result += Visibility::convert(mVisibility);
//	result += " " + LanguageFeatureState::convert(mLanguageFeatureState);
	result += " " + Typename() + " " + getName();
//	result += " " + Mutability::convert(mMutability);

	if ( isAtomicType() ) {
		result += " = " + getValue().toStdString();
	}
	else {
		result += " {\n";

		for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
			result += (*it)->ToString(indent + 1) + "\n";
		}

		for ( Symbols::const_iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
			if ( it->first == IDENTIFIER_BASE || it->first == IDENTIFIER_THIS ||
				 !it->second || it->second->getSymbolType() != Symbol::IType::ObjectSymbol ) {
				continue;
			}

			result += it->second->ToString(indent + 1) + "\n";
		}

		result += ::Utils::Tools::indent(indent) + "}";
	}

	return result;
}


}
}
