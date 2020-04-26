
// Header
#include "Object.h"

// Library includes
#include <utility>

// Project includes
#include <Core/AST/TreeInterpreter.h>
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Runtime/BuildInTypes/VoidObject.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/VirtualMachine/Controller.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace Slang {
namespace Runtime {


Object::Object()
: MethodScope(ANONYMOUS_OBJECT, nullptr),
  ObjectSymbol(ANONYMOUS_OBJECT),
  mBluePrint(nullptr),
  mFilename(ANONYMOUS_OBJECT),
  mIsAtomicType(false),
  mIsReference(false),
  mQualifiedOuterface(ANONYMOUS_OBJECT),
  mQualifiedTypename(ANONYMOUS_OBJECT),
  mTypename(ANONYMOUS_OBJECT)
{
	mThis = this;
}

Object::Object(const std::string& name, std::string filename, const std::string& type, const AtomicValue& value)
: MethodScope(name, nullptr),
  ObjectSymbol(name),
  mBluePrint(nullptr),
  mFilename(std::move(filename)),
  mIsAtomicType(false),
  mIsReference(false),
  mQualifiedOuterface(type),
  mQualifiedTypename(type),
  mTypename(type),
  mValue(value)
{
	mThis = this;
}

Object::~Object()
{
	if ( this != mThis ) {
		Controller::Instance().memory()->remove(mReference);
	}
}

Object& Object::operator= (const Object& other)
{
	if ( this != &other ) {
		mBluePrint = other.mBluePrint;
		mBluePrintType = other.mBluePrintType;
		mFilename = other.mFilename;
		mInheritance = other.mInheritance;
		mIsAtomicType = other.mIsAtomicType;
		mIsReference = other.mIsReference;
		mMemoryLayout = other.mMemoryLayout;
		mParent = other.mParent;
		mScopeName = other.mScopeName;
		mScopeType = other.mScopeType;
		mValue = other.mValue;

		mQualifiedOuterface = other.mQualifiedOuterface;
		mQualifiedTypename = other.mQualifiedTypename;
		mTypename = other.mTypename;

		setLanguageFeatureState(other.getLanguageFeatureState());
		setMember(other.isMember());
		setMutability(other.getMutability());

		assignReference(other.mReference);
	}

	return *this;
}

void Object::assign(const Object& other)
{
	if ( this != &other ) {
		mBluePrint = other.mBluePrint;
		mBluePrintType = other.mBluePrintType;
		mFilename = other.mFilename;
		mInheritance = other.mInheritance;
		mIsAtomicType = other.mIsAtomicType;
		mMemoryLayout = other.mMemoryLayout;
		mParent = other.mParent ? other.mParent : mParent;
		mScopeName = other.mScopeName;
		mScopeType = other.mScopeType;

		if ( mQualifiedOuterface == NULL_TYPE ) {
			mQualifiedOuterface = other.mQualifiedOuterface;
		}
		mQualifiedTypename = other.mQualifiedTypename;
		mTypename = other.mTypename;

		mIsReference = other.mIsReference;
		if ( mIsReference && other.mIsReference ) {
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
	}
	else {
		mThis = this;
	}

	if ( old.isValid() ) {
		Controller::Instance().memory()->remove(old);
	}
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
				throw Common::Exceptions::ParameterCountMismatch("atomic types only support one constructor parameter");
			}

			setValue(params.front().value());
		}

		return controlflow;
	}

	// check if we have implemented a constructor with the given amount and type of parameters
	// if a specialized constructor is implemented, the default constructor cannot be used
	Common::Method *constructor = dynamic_cast<Common::Method*>(resolveMethod(RESERVED_WORD_CONSTRUCTOR, params, true, Visibility::Protected));
	if ( constructor ) {
		VoidObject tmp;

		controlflow = Controller::Instance().thread(0)->execute(mThis, constructor, params, &tmp);

		if ( controlflow != ControlFlow::Normal ) {
			return controlflow;
		}
	}
	else {
		// no appropriate constructor found
		throw Common::Exceptions::Exception(QualifiedTypename() + ": no appropriate constructor found");
	}

	return controlflow;
}

void Object::defineMember(const std::string& name, Symbol* symbol)
{
	MethodScope::define(name, symbol);
}

void Object::defineMethod(const std::string& name, Common::Method* method)
{
	// try to override abstract methods a.k.a. implement an interface method
	auto* old = dynamic_cast<Common::Method*>(resolveMethod(method->getName(), method->provideSignature(), true, Visibility::Designtime));
	if ( old && old->isAbstractMethod() ) {
		Runtime::Object* base = dynamic_cast<Runtime::Object*>(resolve(IDENTIFIER_BASE, true, Visibility::Designtime));
		base->undefineMethod(old);

		delete old;
	}

	MethodScope::defineMethod(name, method);
}

void Object::deinit()
{
	garbageCollector();
}

ControlFlow::E Object::Destructor()
{
	ControlFlow::E controlflow = ControlFlow::Normal;

	if ( !mIsAtomicType ) {
		ParameterList params;

		// only execute destructor if one is present
		Common::Method *destructor = dynamic_cast<Common::Method*>(resolveMethod(RESERVED_WORD_DESTRUCTOR, params, true, Visibility::Private));
		if ( destructor ) {
			VoidObject tmp;

			controlflow = Controller::Instance().thread(0)->execute(mThis, destructor, params, &tmp);

			if ( controlflow != ControlFlow::Normal ) {
				return controlflow;
			}
		}
	}

	return controlflow;
}

ControlFlow::E Object::execute(Object *result, const std::string& name, const ParameterList& params)
{
	auto *method = dynamic_cast<Common::Method*>(resolveMethod(name, params, false, Visibility::Private));
	if ( !method ) {
		throw Common::Exceptions::UnknownIdentifier("unknown method '" + QualifiedTypename() + "." + name + "' or method with invalid parameter count called!");
	}

	return Controller::Instance().thread(0)->execute(mThis, method, params, result);
}

void Object::garbageCollector()
{
	for ( auto mMethod : mMethods ) {
		undefine(mMethod->getName());

		delete mMethod;
	}

	Symbols tmp = mSymbols;

	for ( auto& symIt : tmp ) {
		if ( symIt.first != IDENTIFIER_BASE &&
			 symIt.first != IDENTIFIER_THIS &&
			 symIt.second && symIt.second->getSymbolType() == Symbol::IType::ObjectSymbol ) {
			delete symIt.second;
		}

		mSymbols.erase(symIt.first);
	}
}

Designtime::BluePrintObject* Object::getBluePrint() const
{
	return mBluePrint;
}

const Reference& Object::getReference() const
{
	return mReference;
}

AtomicValue Object::getValue() const
{
	if ( mThis != this ) {
		return mThis->getValue();
	}

	return mValue;
}

bool Object::isAbstract() const
{
	if ( mThis != this ) {
		return mThis->isAbstract();
	}

	for ( auto& mMethod : mMethods ) {
		if ( mMethod->isAbstractMethod() ) {
			return true;
		}
	}

	return mBluePrintType == BlueprintType::Interface;
}

bool Object::isAtomicType() const
{
	return mIsAtomicType;
}

bool Object::isEnumerationValue() const
{
	return mBluePrintType == BlueprintType::Enum;
}

bool Object::isInstanceOf(const std::string& type) const
{
	if ( type.empty() ) {
		return false;
	}

	if ( QualifiedTypename() == type ) {
		return true;
	}

	for ( const auto& it : mInheritance ) {
		if ( it.second->isInstanceOf(type) ) {
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

	return mReference.isValid();
}

void Object::operator_assign(const Object *other)
{
	if ( other->isInstanceOf(mQualifiedTypename) ) {
		assign(*other);
		return;
	}

	ParameterList params;
	params.push_back(Parameter::CreateRuntime(mQualifiedTypename, mValue, mReference));

	::Slang::MethodSymbol* value_operator = other->resolveMethod("=operator", params, false, Visibility::Public);
	if ( value_operator ) {
		Controller::Instance().thread(0)->execute(other->getThis(), dynamic_cast<Common::Method*>(value_operator), params, this);
		return;
	}

	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_bitand(const Object *other)
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator&: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_bitcomplement(const Object *other)
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator~: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_bitor(const Object *other)
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator|: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool Object::operator_bool() const
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator bool(): for " + QualifiedTypename() + " not supported");
}

void Object::operator_divide(const Object *other)
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator/: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool Object::operator_equal(const Object *other)
{
	if ( mIsReference && other->mIsReference ) {
		return mReference == other->mReference;
	}

	if ( QualifiedTypename() == NULL_TYPE && (other->QualifiedTypename() == NULL_TYPE || other->QualifiedTypename() == _object) ) {
		return isValid() == other->isValid();
	}

	//throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator==: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");

	return mValue.toInt() == other->mValue.toInt() && mReference == other->mReference;
}

bool Object::operator_greater(const Object *other)
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator>: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool Object::operator_greater_equal(const Object *other)
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator>=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool Object::operator_less(const Object *other)
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator<: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

bool Object::operator_less_equal(const Object *other)
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator<=: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_modulo(const Object *other)
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator%: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_multiply(const Object *other)
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator*: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_plus(const Object *other)
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator+: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_subtract(const Object *other)
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator-: conversion from " + other->QualifiedTypename() + " to " + QualifiedTypename() + " not supported");
}

void Object::operator_unary_decrement()
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator--: for " + QualifiedTypename() + " not supported");
}

void Object::operator_unary_increment()
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator++: for " + QualifiedTypename() + " not supported");
}

void Object::operator_unary_minus()
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator unary -: for " + QualifiedTypename() + " not supported");
}

void Object::operator_unary_not()
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator unary !: for " + QualifiedTypename() + " not supported");
}

void Object::operator_unary_plus()
{
	throw Runtime::Exceptions::InvalidOperation(QualifiedTypename() + ".operator unary +: for " + QualifiedTypename() + " not supported");
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
		Object* base = dynamic_cast<Object*>(MethodScope::resolve("base", true, Visibility::Designtime));
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

Slang::MethodSymbol* Object::resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope, Visibility::E visibility) const
{
	if ( mThis != this ) {
		return mThis->resolveMethod(name, params, onlyCurrentScope, visibility);
	}

	// (1) look in current scope
	Slang::MethodSymbol *result = MethodScope::resolveMethod(name, params, true, visibility);

	// (2) check inheritance
	// we cannot go the short is-result-already-set way here because one of our ancestor methods could be marked as final
	Symbol* base = MethodScope::resolve("base", true, Visibility::Designtime);
	if ( base && base->getSymbolType() == Symbol::IType::ObjectSymbol ) {
		Slang::MethodSymbol *tmp = dynamic_cast<Object*>(base)->resolveMethod(name, params, onlyCurrentScope, visibility < Visibility::Protected ? Visibility::Protected : visibility);
		if ( !result || (tmp && tmp->isFinalMethod()) ) {
			result = tmp;
		}
	}

	// (3) if we still haven't found something also look in other scopes
	if ( !result || !result->isFinalMethod() ) {
		if ( !onlyCurrentScope ) {
			Slang::MethodSymbol *tmp = MethodScope::resolveMethod(name, params, false, visibility);

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

void Object::setIsReference(bool state)
{
	mIsReference = state;
}

void Object::setParent(IScope *scope)
{
	mParent = scope;
}

void Object::setReference(const Reference& reference)
{
	mIsReference = true;
	mReference = reference;
}

void Object::setValue(const AtomicValue& value)
{
	if ( mThis != this ) {
		return mThis->setValue(value);
	}

	mValue = value;
}

std::string Object::ToString(unsigned int indent) const
{
	if ( mThis != this ) {
		return mThis->ToString(indent);
	}

	std::string result;
	result += ::Utils::Tools::indent(indent);
	result += " " + MemoryLayout::convert(mMemoryLayout);
	if ( mLanguageFeatureState != LanguageFeatureState::Stable ) {
		result += Visibility::convert(mVisibility);
	}
	result += " " + QualifiedTypename() + " " + getName();
	result += " " + Mutability::convert(mMutability);

	if ( isAtomicType() ) {
		result += " = '" + getValue().toStdString() + "'";
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

		for ( const auto& mSymbol : mSymbols ) {
			if ( mSymbol.first == IDENTIFIER_THIS || !mSymbol.second ) {
				continue;
			}

			switch ( mSymbol.second->getSymbolType() ) {
				case Symbol::IType::BluePrintObjectSymbol:
				case Symbol::IType::MethodSymbol:
				case Symbol::IType::NamespaceSymbol:
					continue;
				case Symbol::IType::ObjectSymbol:
					result += mSymbol.second->ToString(indent + 1) + "\n";
					break;
			}
		}

		result += ::Utils::Tools::indent(indent) + "}";
	}

	return result;
}


}
}
