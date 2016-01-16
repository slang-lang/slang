
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
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Object::Object()
: LocalScope(ANONYMOUS_OBJECT, 0),
  ObjectSymbol(ANONYMOUS_OBJECT),
  mIsAtomicType(true),
  mRepository(0),
  mValue(VALUE_NONE),
  mConstructed(false)
{
}

Object::Object(const Object& other)
: LocalScope(other.getName(), 0),
  ObjectSymbol(other.getName()),
  BluePrint(other.mTypename, other.mFilename),
  mIsAtomicType(other.mIsAtomicType),
  mRepository(other.mRepository),
  mConstructed(other.mConstructed)
{
	mTokens = other.mTokens;

	setValue(other.getValue());

	setConst(other.isConst());
	setFinal(other.isFinal());
	//setStatic(other.isStatic());

	// register new members
	for ( MemberCollection::const_iterator it = other.mMembers.begin(); it != other.mMembers.end(); ++it ) {
		copyMember(it->second);
	}

	// register new methods
	for ( MethodCollection::const_iterator it = other.mMethods.begin(); it != other.mMethods.end(); ++it ) {
		Method *m = new Method(this, (*it)->name(), (*it)->type());
		*m = *(*it);

		addMethod(m);
	}
}

Object::Object(const std::string& type, const std::string& filename)
: LocalScope(ANONYMOUS_OBJECT, 0),
  ObjectSymbol(ANONYMOUS_OBJECT),
  BluePrint(type, filename),
  mIsAtomicType(true),
  mRepository(0),
  mValue(VALUE_NONE),
  mConstructed(false)
{
}

Object::Object(const std::string& name, const std::string& filename, const std::string& type, const std::string& value)
: LocalScope(name, 0),
  ObjectSymbol(name),
  BluePrint(type, filename),
  mIsAtomicType(true),
  mRepository(0),
  mValue(value),
  mConstructed(false)
{
}

Object::~Object()
{
	garbageCollector();

/*
	if ( mRepository ) {
		mRepository->removeReference(this);
	}
*/
}

Object& Object::operator= (const Object& other)
{
	if ( this != &other ) {
		if ( !mConstructed ) {
			mConstructed = other.mConstructed;
		}
		if ( !mRepository ) {
			mRepository = other.mRepository;
		}

		mFilename = other.mFilename;
		mTokens = other.mTokens;
		mTypename = other.Typename();

		setValue(other.getValue());

		//setConst(other.isConst());
		//setFinal(other.isFinal());
		//setStatic(other.isStatic());

		// unregister current members
		for ( MemberCollection::const_iterator it = mMembers.begin(); it != mMembers.end(); ) {
			undefine(it->first, it->second);

			mRepository->removeReference(it->second);
			it = mMembers.erase(it);
		}
		mMembers.clear();

		// unregister old methods
		for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ) {
			undefine((*it)->getName(), (*it));

			delete (*it);
			it = mMethods.erase(it);
		}
		mMethods.clear();

		// register new members
		for ( MemberCollection::const_iterator it = other.mMembers.begin(); it != other.mMembers.end(); ++it ) {
			addMember(it->second);
		}

		// register new methods
		for ( MethodCollection::const_iterator it = other.mMethods.begin(); it != other.mMethods.end(); ++it ) {
			Method *m = new Method(this, (*it)->name(), (*it)->type());
			*m = *(*it);

			addMethod(m);
		}
	}

	return *this;
}

void Object::addMember(Object *member)
{
	assert(member);

	if ( mMembers.find(member->getName()) != mMembers.end() ) {
		throw Utils::Exceptions::DuplicateIdentifer("duplicate member '" + member->getName() + "' added");
	}

	mMembers.insert(std::make_pair(member->getName(), member));

	mRepository->addReference(member);

	define(member->getName(), member);
}

void Object::addMethod(Method *method)
{
	assert(method);

	MethodCollection::iterator tmpIt;
	if ( findMethod(method->name(), method->provideSignature(), tmpIt) ) {
		throw Utils::Exceptions::DuplicateIdentifer("duplicate method '" + method->getName() + "' added with same signature");
	}

	method->setOwner(this);
	method->setRepository(mRepository);

	mMethods.insert(method);

	//define(method->getName(), method);	// does not allowed method overloading..
}

void Object::addParent(const std::string& parent)
{
	for ( StringList::const_iterator it = mParents.begin(); it != mParents.end(); ++it ) {
		if ( (*it) == parent ) {
			throw Utils::Exceptions::Exception("duplicate inheritance detected");
		}
	}

	mParents.push_back(parent);
}

void Object::connectRepository(Repository *r)
{
	assert(r);
	mRepository = r;
}

void Object::Constructor(const ParameterList& params)
{
	if ( mConstructed ) {
		throw Utils::Exceptions::Exception("can not construct object '" + getName() + "' multiple times");
	}

	// only execute constructor if one is present
	if ( hasMethod(Typename(), params) ) {
		VoidObject tmp;
		execute(&tmp, Typename(), params);
	}

	// set after executing constructor in case any exceptions have been thrown
	mConstructed = true;
}

void Object::copyMember(Object *member)
{
	assert(member);

	if ( mMembers.find(member->getName()) != mMembers.end() ) {
		throw Utils::Exceptions::DuplicateIdentifer("duplicate member '" + member->getName() + "' added");
	}

	// create object instance
	Object *object = mRepository->createInstance(member->Typename(), member->getName());

	// and fill it with life
	*object = *member;

	mMembers.insert(std::make_pair(member->getName(), member));
}

void Object::Destructor()
{
	if ( mConstructed ) {
		// only execute destructor if one is present
		if ( hasMethod("~" + getName(), ParameterList()) ) {
			VoidObject object;
			execute(&object, "~" + Typename(), ParameterList());
		}
	}
	else {
		// either the destructor has already been executed
		// or the constructor has never been called successfully!
		//throw Utils::Exceptions::Exception("can not destroy object '" + name() + "' which has not been constructed");
	}

	garbageCollector(true);

	// set after executing destructor in case any exceptions have been thrown
	mConstructed = false;
}

ControlFlow::E Object::execute(Object *result, const std::string& method, const ParameterList& params, const Method* caller)
{
	OSdebug("execute('" + method + "', [" + toString(params) + "])");

	MethodCollection::iterator methodIt;
	bool success = findMethod(method, params, methodIt);
	if ( !success ) {
		throw Utils::Exceptions::UnknownIdentifer("unknown method '" + method + "' or method with invalid parameter count called!");
	}

	// are we called from a colleague method?
	bool callFromMethod = caller && (caller->getOwner() == this);

	// check visibility:
	// colleague methods can always call us,
	// for calls from non-member functions the method visibility must be public (or protected if they belong to the same object hierarchy)
	if ( !callFromMethod && (*methodIt)->visibility() != Visibility::Public ) {
		throw Utils::Exceptions::VisibilityError("invalid visibility: " + method);
	}

	// execute our member method
	return (*methodIt)->execute(params, result);
}

bool Object::findMember(const std::string& m, Object::MemberCollection::const_iterator& mIt) const
{
	for ( MemberCollection::const_iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == m /*&& it->second.visibility() == Visibility::Public*/ ) {
			mIt = it;
			return true;
		}
	}

	std::string member, parent;
	Tools::split(m, parent, member);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::const_iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == parent ) {
			return it->second->findMember(member, mIt);
		}
	}

	return false;
}

bool Object::findMethod(const std::string& m, MethodCollection::const_iterator& mIt) const
{
	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( (*it)->name() == m /*&& it->visibility() == Visibility::Public*/ ) {
			mIt = it;
			return true;
		}
	}

	std::string method, parent;
	Tools::split(m, parent, method);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::const_iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == parent ) {
			return it->second->findMethod(method, mIt);
		}
	}

	return false;
}

bool Object::findMethod(const std::string& m, const ParameterList& params, MethodCollection::const_iterator& mIt) const
{
	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( (*it)->name() == m && (*it)->isSignatureValid(params) ) {
			mIt = it;
			return true;
		}
	}

	std::string method, parent;
	Tools::split(m, parent, method);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::const_iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == parent ) {
			return it->second->findMethod(method, params, mIt);
		}
	}

	return false;
}

void Object::garbageCollector(bool force)
{
	// members are objects, so they will get cleaned up by our repository
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		mRepository->removeReference(it->second);
	}
	mMembers.clear();

	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		(*it)->garbageCollector(force);
		delete (*it);
	}
	mMethods.clear();
}

Object* Object::getMember(const std::string& symbol) const
{
	std::string member, parent;
	Tools::split(symbol, parent, member);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::const_iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == symbol ) {
			return it->second;
		}

		if ( it->second->getName() == parent ) {
			return it->second->getMember(member);
		}
	}

	return 0;
}

const std::string& Object::getTypeName() const
{
	return Typename();
}

std::string Object::getValue() const
{
	return mValue;
}

bool Object::hasMethod(const std::string& symbol) const
{
	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( (*it)->getName() == symbol ) {
			return true;
		}
	}

	std::string method, parent;
	Tools::split(symbol, parent, method);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::const_iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == parent ) {
			if ( it->second->hasMethod(method) ) {
				return true;
			}
		}
	}

	return false;
}

bool Object::hasMethod(const std::string& symbol, const ParameterList& params) const
{
	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( (*it)->name() == symbol ) {
			if ( (*it)->isSignatureValid(params) ) {
				return true;
			}
		}
	}

	std::string method, parent;
	Tools::split(symbol, parent, method);

	// loop through all members and ask them if this method belongs to them
	for ( MemberCollection::const_iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == parent ) {
			if ( it->second->hasMethod(method, params) ) {
				return true;
			}
		}
	}

	return false;
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
			result += (*it)->type() + " " + (*it)->name();

			MethodCollection::const_iterator copy = it;
			if ( ++copy != mMethods.end() ) {
				result += ", \n";
			}
		}
		for ( MemberCollection::const_iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
			result += it->second->ToString();

			MemberCollection::const_iterator copy = it;
			if ( ++copy != mMembers.end() ) {
				result += ", ";
			}
		}

		result += " }";
	}

	return result;
}


}
