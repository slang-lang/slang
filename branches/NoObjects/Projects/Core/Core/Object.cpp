
// Header
#include "Object.h"

// Library includes

// Project includes
#include <Core/Interfaces/IPrinter.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Memory.h"
#include "Repository.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Object::Object()
: LocalScope("", 0),
  mIsAtomicType(false),
  mRepository(0),
  mConstructed(false),
  mPrinter(0)
{
}

Object::Object(const std::string& type, const std::string& filename)
: LocalScope("", 0),
  BluePrint(type, filename),
  mIsAtomicType(false),
  mRepository(0),
  mConstructed(false),
  mPrinter(0)
{
}

Object::Object(const std::string& name, const std::string& filename, const std::string& type, const std::string& value)
: LocalScope(name, 0),
  BluePrint(type, filename),
  mIsAtomicType(false),
  mRepository(0),
  mConstructed(false),
  mName(name),
  mPrinter(0),
  mValue(value)
{
}

Object::~Object()
{
	garbageCollector();
}

void Object::operator= (const Object& other)
{
	if ( this == &other ) {
		return;
	}

	if ( !mConstructed ) {
		mConstructed = other.mConstructed;
	}
	if ( !mPrinter ) {
		mPrinter = other.mPrinter;
	}
	if ( !mRepository ) {
		mRepository = other.mRepository;
	}

	mTokens = other.mTokens;
	mTypename = other.Typename();
	mValue = other.getValue();

	//this->setConst(other.isConst());
	this->setFinal(other.isFinal());
	this->setStatic(other.isStatic());

	// unregister current members
	for ( MemberCollection::const_iterator it = mMembers.begin(); it != mMembers.end(); ) {
		mRepository->removeReference(it->second);
		it = mMembers.erase(it);
	}
	mMembers.clear();

	// register new members
	for ( MemberCollection::const_iterator it = other.mMembers.begin(); it != other.mMembers.end(); ++it ) {
		addMember(it->second);
	}

	// unregister old methods
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ) {
		delete (*it);
		it = mMethods.erase(it);
	}
	mMethods.clear();

	// register new methods
	for ( MethodCollection::const_iterator it = other.mMethods.begin(); it != other.mMethods.end(); ++it ) {
		Method *m = new Method(this, (*it)->name(), (*it)->type());
		*m = *(*it);

		addMethod(m);
	}
}

void Object::addMember(Object *m)
{
	assert(m);

	if ( mMembers.find(m->name()) != mMembers.end() ) {
		throw Utils::DuplicateIdentiferException("duplicate member '" + m->name() + "' added");
	}

	mMembers.insert(std::make_pair(m->name(), m));

	mRepository->addReference(m);
}

void Object::addMethod(Method *m)
{
	assert(m);

	if ( mMethods.find(m) != mMethods.end() ) {
		throw Utils::DuplicateIdentiferException("duplicate method '" + m->name() + "' added with same signature");
	}

	m->setOwner(this);
	m->setRepository(mRepository);

	mMethods.insert(m);
}

void Object::addParent(const std::string& parent)
{
	for ( StringList::const_iterator it = mParents.begin(); it != mParents.end(); ++it ) {
		if ( (*it) == parent ) {
			throw Utils::Exception("duplicate inheritance detected");
		}
	}

	mParents.push_back(parent);
}

void Object::connectPrinter(IPrinter *p)
{
	mPrinter = p;
}

void Object::connectRepository(Repository *r)
{
	assert(r);

	mRepository = r;
}

void Object::Constructor(const ParameterList& params)
{
	if ( mConstructed ) {
		throw Utils::Exception("can not construct object '" + name() + "' multiple times");
	}

	if ( !mConstructed ) {
		// only execute constructor if one is present
		if ( hasMethod(Typename(), params) ) {
			Object object;
			execute(&object, Typename(), params);
		}

		// set after executing constructor
		// in case any exceptions have been thrown
		mConstructed = true;
	}
	else {
		// the constructor has already been executed!
		//throw Utils::Exception("can not create object '" + name() + "' which has already been constructed");
	}
}

void Object::Destructor()
{
	if ( mConstructed ) {
		// only execute destructor if one is present
		if ( hasMethod("~" + getName(), ParameterList()) ) {
			Object object;
			execute(&object, "~" + Typename(), ParameterList());
		}
	}
	else {
		// either the destructor has already been executed
		// or the constructor has never been called successfully!
		//throw Utils::Exception("can not destroy object '" + name() + "' which has not been constructed");
	}

	garbageCollector(true);

	// set after executing destructor
	// in case any exceptions have been thrown
	mConstructed = false;
}

void Object::execute(Object *result, const std::string& method, const ParameterList& params, const Method* caller)
{
	//OSdebug("execute('" + method + "', [" + toString(params) + "])");

	MethodCollection::iterator mIt;
	bool success = findMethod(method, params, mIt);
	if ( !success ) {
		throw Utils::UnknownIdentifer("unknown method '" + method + "' or method with invalid parameter count called!");
	}

	// are we called from a colleague method?
	bool callFromMethod = caller && (caller->getOwner() == this);

	Method *mPtr = (*mIt);

	// check visibility:
	// colleague method functions can always call us,
	// for calls from non-member functions the method visibility must be public (or protected if they belong to the same object hirarchy)
	if ( !callFromMethod && mPtr->visibility() != Visibility::Public ) {
		throw Utils::VisibilityError("invalid visibility: " + method);
	}

	try {
		// execute our member method
		*result = mPtr->execute(params);
	}
	catch ( Utils::Exception &e ) {
		// catch and log all errors that occured during method execution
		OSerror(e.what());

		mPrinter->print(ToString());

		throw;
	}
}

bool Object::findMember(const std::string& m, Object::MemberCollection::iterator& mIt)
{
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == m /*&& it->second.visibility() == Visibility::Public*/ ) {
			mIt = it;
			return true;
		}
	}

	std::string member, parent;
	Tools::split(m, parent, member);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == parent ) {
			return it->second->findMember(member, mIt);
		}
	}

	return false;
}

bool Object::findMethod(const std::string& m, MethodCollection::iterator& mIt)
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( (*it)->name() == m /*&& it->visibility() == Visibility::Public*/ ) {
			mIt = it;
			return true;
		}
	}

	std::string method, parent;
	Tools::split(m, parent, method);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == parent ) {
			return it->second->findMethod(method, mIt);
		}
	}

	return false;
}

bool Object::findMethod(const std::string& m, const ParameterList& params, MethodCollection::iterator& mIt)
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( (*it)->name() == m && (*it)->isSignatureValid(params) ) {
			mIt = it;
			return true;
		}
	}

	std::string method, parent;
	Tools::split(m, parent, method);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
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

Object* Object::getMember(const std::string& m)
{
	std::string member, parent;
	Tools::split(m, parent, member);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == m ) {
			return it->second;
		}

		if ( it->second->name() == parent ) {
			return it->second->getMember(member);
		}
	}

	return 0;
}

bool Object::hasMethod(const std::string& m)
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( (*it)->name() == m ) {
			return true;
		}
	}

	std::string method, parent;
	Tools::split(m, parent, method);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == parent ) {
			if ( it->second->hasMethod(method) ) {
				return true;
			}
		}
	}

	return false;
}

bool Object::hasMethod(const std::string& m, const ParameterList& params)
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( (*it)->name() == m ) {
			if ( (*it)->isSignatureValid(params) ) {
				return true;
			}
		}
	}

	std::string method, parent;
	Tools::split(m, parent, method);

	// loop through all members and ask them if this method belongs to them
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
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
	return mConstructed /*&& mValue != "0"*/;
}

const std::string& Object::name() const
{
	return mName;
}

void Object::name(const std::string& name)
{
	mName = name;
}

void Object::operator_assign(Object * /*other*/)
{
	throw Utils::Exception(ToString() + ", operator= not implemented");
}

void Object::operator_divide(Object * /*other*/)
{
	throw Utils::Exception(ToString() + ", operator/ not implemented");
}

void Object::operator_multiply(Object * /*other*/)
{
	throw Utils::Exception(ToString() + ", operator* not implemented");
}

void Object::operator_plus(Object * /*other*/)
{
	throw Utils::Exception(ToString() + ", operator+ not implemented");
}

void Object::operator_subtract(Object * /*other*/)
{
	throw Utils::Exception(ToString() + ", operator- not implemented");
}

IPrinter* Object::providePrinter() const
{
	return mPrinter;
}

std::string Object::ToString() const
{
	std::string result = "Object: " + name() + " <" + Typename() + "> = { ";

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

	return result;
}

void Object::updateMethodOwners()
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		(*it)->setOwner(this);
		(*it)->setRepository(mRepository);
	}
}

const std::string& Object::getValue() const
{
	return mValue;
}

void Object::setValue(const std::string& value)
{
	mValue = value;
}


}
