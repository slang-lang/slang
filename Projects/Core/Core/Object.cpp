
// Header
#include "Object.h"

// Library includes

// Project includes
#include <Core/AST/TreeInterpreter.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Defines.h>
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
  mBase(0),
  mBluePrint(0),
  mFilename(ANONYMOUS_OBJECT),
  mIsAtomicType(false),
  mIsConstructed(false),
  mIsNull(true),
  mQualifiedOuterface(ANONYMOUS_OBJECT),
  mQualifiedTypename(ANONYMOUS_OBJECT),
  mTypename(ANONYMOUS_OBJECT)
{
	mThis = this;
}

Object::Object(const Object& other)
: MethodScope(other.getName(), other.mParent),
  ObjectSymbol(other.getName()),
  mBase(0),
  mBluePrint(other.mBluePrint),
  mFilename(other.mFilename),
  mInheritance(other.mInheritance),
  mIsAtomicType(other.mIsAtomicType),
  mIsConstructed(other.mIsConstructed),
  mIsNull(other.mIsNull),
  mQualifiedOuterface(other.mQualifiedOuterface),
  mQualifiedTypename(other.mQualifiedTypename),
  mTypename(other.mTypename)
{
	mThis = this;

	mImplementationType = other.mImplementationType;
	mParent = other.mParent;
	mScopeName = other.mScopeName;
	mScopeType = other.mScopeType;

	setConst(other.isConst());
	setFinal(other.isFinal());
	setLanguageFeatureState(other.getLanguageFeatureState());
	setMember(other.isMember());

	assignReference(other.mReference);

	setValue(other.mValue);
}

Object::Object(const std::string& name, const std::string& filename, const std::string& type, AtomicValue value)
: MethodScope(name, 0),
  ObjectSymbol(name),
  mBase(0),
  mFilename(filename),
  mIsAtomicType(false),
  mIsConstructed(false),
  mIsNull(false),
  mQualifiedOuterface(type),
  mQualifiedTypename(type),
  mTypename(type),
  mValue(value)
{
	mThis = this;
}

Object::~Object()
{
	if ( mThis == this ) {
		undefine(IDENTIFIER_THIS);
	}

	Controller::Instance().memory()->remove(mReference);

	mBase = 0;
	mThis = 0;
}

Object& Object::operator= (const Object& other)
{
	if ( this != &other ) {
		mBluePrint = other.mBluePrint;
		mFilename = other.mFilename;
		mImplementationType = other.mImplementationType;
		mInheritance = other.mInheritance;
		mIsAtomicType = other.mIsAtomicType;
		mIsConstructed = other.mIsConstructed;
		mIsNull = other.mIsNull;
		mParent = other.mParent;
		mScopeName = other.mScopeName;
		mScopeType = other.mScopeType;
		mValue = other.mValue;

		mQualifiedOuterface = other.mQualifiedOuterface;
		mQualifiedTypename = other.mQualifiedTypename;
		mTypename = other.mTypename;

		setConst(other.isConst());
		setFinal(other.isFinal());
		setLanguageFeatureState(other.getLanguageFeatureState());
		setMember(other.isMember());

		assignReference(other.mReference);
	}

	return *this;
}

void Object::assign(const Object& other, bool overrideType)
{
	if ( this != &other ) {
		mBluePrint = other.mBluePrint;
		mFilename = other.mFilename;
		mImplementationType = other.mImplementationType;
		mInheritance = other.mInheritance;
		mIsAtomicType = other.mIsAtomicType;
		mIsConstructed = other.mIsConstructed;
		mIsNull = other.mIsNull;
		mParent = other.mParent ? other.mParent : mParent;
		mScopeName = other.mScopeName;
		mScopeType = other.mScopeType;

		if ( mQualifiedOuterface == NULL_TYPE || overrideType ) {
			mQualifiedOuterface = other.mQualifiedOuterface;
		}
		mQualifiedTypename = other.mQualifiedTypename;
		mTypename = other.mTypename;

		if ( other.mReference.isValid() ) {
			assignReference(other.mReference);
		}
		else {
			setValue(other.getValue());
		}
	}
}

void Object::addInheritance(const Designtime::Ancestor& ancestor, Object* inheritance)
{
	if ( !inheritance ) {
		throw Common::Exceptions::Exception("invalid inheritance level added!");
	}

	mInheritance.insert(std::make_pair(ancestor, inheritance));
}

void Object::assignReference(const Reference& ref)
{
	Reference old = mReference;

	mReference = ref;
	Controller::Instance().memory()->add(mReference);

	if ( mReference.isValid() ) {
		mThis = Controller::Instance().memory()->get(mReference);
		mBase = mThis->mBase;
	}
	else {
		mThis = this;
		mBase = dynamic_cast<Object*>(MethodScope::resolve("base", true));
	}

	Controller::Instance().memory()->remove(old);
}

bool Object::CanExecuteDefaultConstructor() const
{
	Symbol* anyConstructor = resolve(RESERVED_WORD_CONSTRUCTOR, false, Visibility::Private);
	if ( !anyConstructor ) {
		// no constructor found at all, so we can call our default constructor but it won't do anything besides setting our object to constructed
		return true;
	}

	Symbol* defaultConstructor = resolveMethod(RESERVED_WORD_CONSTRUCTOR, ParameterList(), true, Visibility::Private);

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

	if ( isConstructed() ) {	// prevent multiple instantiations
		throw Common::Exceptions::Exception("can not construct '" + QualifiedTypename() + "' multiple times");
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
	Symbol *symbol = resolve(RESERVED_WORD_CONSTRUCTOR, true, Visibility::Private);
	if ( symbol ) {
		// if a specialized constructor is implemented, the default constructor cannot be used
		Common::Method *constructor = dynamic_cast<Common::Method*>(resolveMethod(RESERVED_WORD_CONSTRUCTOR, params, true, Visibility::Private));
		if ( constructor ) {
			VoidObject tmp;

			controlflow = Controller::Instance().thread(0)->execute(constructor, params, &tmp);

			if ( controlflow != ControlFlow::Normal ) {
				return controlflow;
			}
		}
		else {
			// no appropriate constructor found
			throw Common::Exceptions::Exception(QualifiedTypename() + ": no appropriate constructor found");
		}
	}

/*	// doesn't work properly yet
	// check if all base objects have been constructed correctly
	for ( Inheritance::iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
		if ( !it->second->mIsConstructed ) {
			throw Common::Exceptions::Exception(getName() + "." + QualifiedTypename() + "(): not all base objects have been constructed correctly");
		}
	}
*/

	// set after executing constructor in case any exceptions have been thrown
	setConstructed(true);

	return controlflow;
}

void Object::copy(const Object& other)
{
	if ( this != &other ) {
		mBluePrint = other.mBluePrint;
		mFilename = other.mFilename;
		mImplementationType = other.mImplementationType;
		mInheritance = other.mInheritance;
		mIsAtomicType = other.mIsAtomicType;
		mIsConstructed = other.mIsConstructed;
		mFilename = other.mFilename;
		mParent = other.mParent ? other.mParent : mParent;
		mQualifiedOuterface = other.mQualifiedTypename;
		mQualifiedTypename = other.mQualifiedTypename;
		mScopeName = other.mScopeName;
		mScopeType = other.mScopeType;
		mTypename = other.mTypename;
		mValue = other.mValue;

		if ( mReference.isValid() ) {
			// this object has a reference to a third object
			// we also have to copy this third object by creating a fourth

			assert(!"not implemented");
		}
		else {
			garbageCollector();

			// register this
			define(IDENTIFIER_THIS, this);

			// register new members
			for ( Symbols::const_iterator it = other.mSymbols.begin(); it != other.mSymbols.end(); ++it ) {
				if ( it->first == IDENTIFIER_THIS || !it->second || it->second->getSymbolType() != Symbol::IType::ObjectSymbol) {
					continue;
				}

				Object* source = static_cast<Object*>(it->second);
				Object* target = Controller::Instance().repository()->createInstance(source->QualifiedTypename(), source->getName(), PrototypeConstraints());
				target->copy(*source);

				defineMember(target->getName(), target);
			}

			// register new methods
			for ( MethodCollection::const_iterator it = other.mMethods.begin(); it != other.mMethods.end(); ++it ) {
				// create new method and ...
				Common::Method* method = new Common::Method(this, (*it)->getName(), (*it)->QualifiedTypename());
				// ... copy its data from our template method
				*method = *(*it);

				defineMethod((*it)->getName(), method);
			}
		}
	}
}

void Object::defineMember(const std::string& name, Symbol* symbol)
{
	MethodScope::define(name, symbol);
}

void Object::defineMethod(const std::string& name, Common::Method* method)
{
	// try to override abstract methods a.k.a. implement an interface method
	Common::Method* old = static_cast<Common::Method*>(resolveMethod(method->getName(), method->provideSignature(), true, Visibility::Designtime));
	if ( old && old->isAbstract() ) {
		Runtime::Object* base = dynamic_cast<Runtime::Object*>(resolve(IDENTIFIER_BASE, true, Visibility::Designtime));
		base->undefineMethod(old);

		delete old;
	}

	MethodScope::defineMethod(name, method);

	method->initialize();
}

ControlFlow::E Object::Destructor()
{
	ControlFlow::E controlflow = ControlFlow::Normal;

	if ( isConstructed() && !mIsAtomicType ) {
		ParameterList params;

		// only execute destructor if one is present
		Common::Method *destructor = static_cast<Common::Method*>(resolveMethod(RESERVED_WORD_DESTRUCTOR, params, true, Visibility::Private));
		if ( destructor ) {
			VoidObject tmp;

			controlflow = Controller::Instance().thread(0)->execute(destructor, params, &tmp);

			if ( controlflow != ControlFlow::Normal ) {
				return controlflow;
			}
		}

/*
		// execute parent object destructors
		for ( Inheritance::iterator it = mInheritance.begin(); it != mInheritance.end(); ++it ) {
			controlflow = it->second->Destructor();

			if ( controlflow != ControlFlow::Normal ) {
				return controlflow;
			}
		}
*/
	}

	// set after executing destructor in case any exceptions have been thrown
	setConstructed(false);

	return controlflow;
}

ControlFlow::E Object::execute(Object *result, const std::string& name, const ParameterList& params, const Method* /*caller*/)
{
	if ( !isConstructed() ) {
		// a method is being called although our object has not yet been constructed?
		throw Runtime::Exceptions::NullPointerException("executed method '" + name + "' of uninitialized object '" + QualifiedTypename() + "'");
	}

	Common::Method *method = static_cast<Common::Method*>(resolveMethod(name, params, false, Visibility::Private));
	if ( !method ) {
		throw Common::Exceptions::UnknownIdentifer("unknown method '" + QualifiedTypename() + "." + name + "' or method with invalid parameter count called!");
	}

	return Controller::Instance().thread(0)->execute(method, params, result);
}

bool Object::FromJson(const Json::Value& value)
{
	for ( Json::Value::Members::const_iterator it = value.members().begin(); it != value.members().end(); ++it ) {
		Json::Value sub = (*it);

		Symbol *symbol = resolve(sub.key(), true, Visibility::Designtime);
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
		undefine((*it)->getName());

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

Designtime::BluePrintObject* Object::getBluePrint() const
{
	return mBluePrint;
}

AtomicValue Object::getValue() const
{
	if ( mThis != this ) {
		return mThis->getValue();
	}

	return mValue;
}

void Object::initialize()
{
	// nothing to do here atm
}

bool Object::isAbstract() const
{
	if ( mThis != this ) {
		return mThis->isAbstract();
	}

	bool result = mBase ? mBase->isAbstract() : false;

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

bool Object::isConstructed() const
{
	if ( mThis != this ) {
		return Controller::Instance().memory()->get(mReference)->isConstructed();
	}

	return mIsConstructed;
}

bool Object::isNull() const
{
	return mIsNull;
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
	if ( mIsAtomicType ) {
		return getValue().toBool();
	}

	return isConstructed();
}

void Object::operator_array(const Object *index, Object* result)
{
	std::string subscript = index->QualifiedTypename();

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(subscript, index->getValue(), index->getReference()));

	::ObjectiveScript::MethodSymbol* opMethod = resolveMethod("operator[]", params, false, Visibility::Public);
	if ( opMethod ) {
		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(opMethod), params, result);

		return;
	}

	throw Common::Exceptions::NotImplemented(QualifiedTypename() + ".operator[]: no array subscript operator for " + subscript + " implemented");
}

void Object::operator_assign(const Object *other)
{
	if ( other->isInstanceOf(mQualifiedTypename) ) {
		assign(*other);
		return;
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("=operator", params, false, Visibility::Public);
	if ( value_operator ) {
/*
		Object tmp;

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, &tmp);

		operator_assign(&tmp);
		return;
*/

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, this);
		return;
	}

	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_bitand(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator&: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("&operator", params, false, Visibility::Public);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, false, Visibility::Public);
	}
	if ( value_operator ) {
/*
		Object tmp;

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, &tmp);

		operator_bitand(&tmp);
		return;
*/

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, this);
		return;
	}

	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator&: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_bitcomplement(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator~: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("~operator", params, false, Visibility::Public);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, false, Visibility::Public);
	}
	if ( value_operator ) {
/*
		Object tmp;

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, &tmp);

		operator_bitcomplement(&tmp);
		return;
*/

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, this);
		return;
	}

	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator~: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_bitor(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator|: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("|operator", params, false, Visibility::Public);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, false, Visibility::Public);
	}
	if ( value_operator ) {
/*
		Object tmp;

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, &tmp);

		operator_bitor(&tmp);
		return;
*/

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, this);
		return;
	}

	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator|: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool Object::operator_bool() const
{
	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator bool(): for " + QualifiedTypename() + " not supported");
}

void Object::operator_divide(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator/: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("/operator", params, false, Visibility::Public);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, false, Visibility::Public);
	}
	if ( value_operator ) {
/*
		Object tmp;

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, &tmp);

		operator_divide(&tmp);
		return;
*/

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, this);
		return;
	}

	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator/: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
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
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("==operator", params, false, Visibility::Public);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, false, Visibility::Public);
	}
	if ( value_operator ) {
		Object tmp;

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, &tmp);

		return operator_equal(&tmp);
	}

	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator==: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool Object::operator_greater(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod(">operator", params, false, Visibility::Public);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, false, Visibility::Public);
	}
	if ( value_operator ) {
		Object tmp;

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, &tmp);

		return operator_greater(&tmp);
	}

	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool Object::operator_greater_equal(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod(">=operator", params, false, Visibility::Public);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, false, Visibility::Public);
	}
	if ( value_operator ) {
		Object tmp;

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, &tmp);

		return operator_greater_equal(&tmp);
	}

	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool Object::operator_is(const std::string& type)
{
	if ( type.empty() ) {
		return false;
	}

	if ( mThis ) {
		return mThis->isInstanceOf(type);
	}

	return isInstanceOf(type);
}

bool Object::operator_less(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("<operator", params, false, Visibility::Public);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, false, Visibility::Public);
	}
	if ( value_operator ) {
		Object tmp;

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, &tmp);

		return operator_less(&tmp);
	}

	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool Object::operator_less_equal(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("<=operator", params, false, Visibility::Public);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, false, Visibility::Public);
	}
	if ( value_operator ) {
		Object tmp;

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, &tmp);

		return operator_less_equal(&tmp);
	}

	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_modulo(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator%: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("%operator", params, false, Visibility::Public);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, false, Visibility::Public);
	}
	if ( value_operator ) {
/*
		Object tmp;

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, &tmp);

		operator_modulo(&tmp);
		return;
*/

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, this);
		return;
	}

	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator%: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_multiply(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator*: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("*operator", params, false, Visibility::Public);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, false, Visibility::Public);
	}
	if ( value_operator ) {
/*
		Object tmp;

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, &tmp);

		operator_multiply(&tmp);
		return;
*/

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, this);
		return;
	}

	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator*: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_plus(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator+: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("+operator", params, false, Visibility::Public);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, false, Visibility::Public);
	}
	if ( value_operator ) {
/*
		Object tmp;

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, &tmp);

		operator_plus(&tmp);
		return;
*/

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, this);
		return;
	}

	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator+: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_subtract(const Object *other)
{
	if ( !other->isValid() ) {
		throw Runtime::Exceptions::NullPointerException(QualifiedTypename() + ".operator-: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::ObjectiveScript::MethodSymbol* value_operator = other->resolveMethod("-operator", params, false, Visibility::Public);
	if ( !value_operator ) {
		value_operator = other->resolveMethod("=operator", params, false, Visibility::Public);
	}
	if ( value_operator ) {
/*
		Object tmp;

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, &tmp);

		operator_subtract(&tmp);
		return;
*/

		Controller::Instance().thread(0)->execute(static_cast<Common::Method*>(value_operator), params, this);
		return;
	}

	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator-: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_unary_decrement()
{
	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator--: for " + QualifiedTypename() + " not supported");
}

void Object::operator_unary_increment()
{
	throw Common::Exceptions::Exception(QualifiedTypename() + ".operator++: for " + QualifiedTypename() + " not supported");
}

void Object::operator_unary_minus()
{
	throw Common::Exceptions::NotImplemented(QualifiedTypename() + ".operator unary -: for " + QualifiedTypename() + " not supported");
}

Symbol* Object::resolve(const std::string& name, bool onlyCurrentScope, Visibility::E visibility) const
{
	if ( mThis != this ) {
		return mThis->resolve(name, onlyCurrentScope, visibility);
	}

	// (1) look only in current scope
	Symbol *result = MethodScope::resolve(name, true, visibility);

	// (2) check inheritance
	if ( !result ) {
		Object* base = dynamic_cast<Object*>(MethodScope::resolve("base", true));
		if ( base && base->getSymbolType() == Symbol::IType::ObjectSymbol && !onlyCurrentScope ) {
			result = base->resolve(name, onlyCurrentScope, visibility < Visibility::Protected ? Visibility::Protected : visibility);
		}
	}

	// (3) if we still haven't found something also look in other scopes
	if ( !result && !onlyCurrentScope ) {
		result = MethodScope::resolve(name, false, visibility);
	}

	return result;
}

ObjectiveScript::MethodSymbol* Object::resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope, Visibility::E visibility) const
{
	if ( mThis != this ) {
		return mThis->resolveMethod(name, params, onlyCurrentScope, visibility);
	}

	// (1) look in current scope
	ObjectiveScript::MethodSymbol *result = MethodScope::resolveMethod(name, params, true, visibility);

	// (2) check inheritance
	// we cannot go the short is-result-already-set way here because one of our ancestor methods could be marked as final
	Symbol* base = MethodScope::resolve("base", true);
	if ( base && base->getSymbolType() == Symbol::IType::ObjectSymbol /*&& !onlyCurrentScope*/ ) {
		ObjectiveScript::MethodSymbol *tmp = dynamic_cast<Object*>(base)->resolveMethod(name, params, onlyCurrentScope, visibility < Visibility::Protected ? Visibility::Protected : visibility);
		if ( !result || (tmp && tmp->isFinal()) ) {
			result = tmp;
		}
	}

	// (3) if we still haven't found something also look in other scopes
	if ( !result || !result->isFinal() ) {
		if ( !onlyCurrentScope ) {
			ObjectiveScript::MethodSymbol *tmp = MethodScope::resolveMethod(name, params, false, visibility);

			if ( tmp ) {
				result = tmp;
			}
		}
	}

	return result;
}

void Object::setBluePrint(Designtime::BluePrintObject* blueprint)
{
	mBluePrint = blueprint;
}

void Object::setConstructed(bool state)
{
	if ( mThis != this ) {
		Controller::Instance().memory()->get(mReference)->setConstructed(state);
		return;
	}

	mIsConstructed = state;
}

void Object::setParent(IScope *scope)
{
	mParent = scope;
}

void Object::setValue(AtomicValue value)
{
	if ( mThis != this ) {
		return mThis->setValue(value);
	}

	mValue = value;
}

Json::Value Object::ToJson() const
{
	Json::Value result;

	for ( Symbols::const_iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
		if ( it->first == IDENTIFIER_BASE ) {
			result.addMember(it->first, dynamic_cast<Object*>(it->second)->ToJson());
		}

		if ( it->first == IDENTIFIER_BASE || it->first == IDENTIFIER_THIS ||
			 !it->second || it->second->getSymbolType() != Symbol::IType::ObjectSymbol ) {
			continue;
		}

		Object *obj = dynamic_cast<Object*>(it->second);

		result.addMember(it->first, obj->getValue().toStdString());
	}

	return result;
}

std::string Object::ToString(unsigned int indent) const
{
	if ( mThis != this ) {
		return mThis->ToString(indent);
	}

	std::string result;
	result += ::Utils::Tools::indent(indent);
	result += Visibility::convert(mVisibility);
	//result += " " + LanguageFeatureState::convert(mLanguageFeatureState);
	result += " " + QualifiedTypename() + " " + getName();
	result += " " + Mutability::convert(mMutability);

	if ( isAtomicType() ) {
		result += " = " + getValue().toStdString();
	}
	else if ( !isValid() ) {
		result += " = null";
	}
	else {
		result += " {\n";

/*
		for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
			result += (*it)->ToString(indent + 1) + "\n";
		}
*/

		for ( Symbols::const_iterator it = mSymbols.begin(); it != mSymbols.end(); ++it ) {
			if ( it->first == IDENTIFIER_THIS || !it->second ) {
				continue;
			}

			switch ( it->second->getSymbolType() ) {
				case Symbol::IType::BluePrintEnumSymbol:
				case Symbol::IType::BluePrintObjectSymbol:
				case Symbol::IType::MethodSymbol:
				case Symbol::IType::NamespaceSymbol:
					continue;
				case Symbol::IType::ObjectSymbol:
					result += it->second->ToString(indent + 1) + "\n";
					break;
			}
		}

		result += ::Utils::Tools::indent(indent) + "}";
	}

	return result;
}


}
}
