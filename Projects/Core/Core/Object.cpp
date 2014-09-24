
// Header
#include "Object.h"

// Library includes

// Project includes
#include "Exceptions.h"
#include "Repository.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Object::Object()
: mConstructed(false),
  mPrinter(0),
  mRepository(0)
{
}

Object::Object(const std::string& type, const std::string& filename)
: ObjectBluePrint(type, filename),
  Variable("", type, ""),
  mConstructed(false),
  mPrinter(0),
  mRepository(0)
{
}

Object::Object(const std::string& name, const std::string& filename, const std::string& type, const std::string& value)
: ObjectBluePrint(type, filename),
  Variable(name, type, value),
  mConstructed(false),
  mPrinter(0),
  mRepository(0)
{
}

Object::~Object()
{
	if ( mConstructed ) {
		// we have not yet been destroyed
		// so execute our destructor
		Destructor();
	}
}

void Object::addMember(Object m)
{
	os_debug("addMember(" + m.name() + ")");

	if ( mMembers.find(m.name()) != mMembers.end() ) {
		throw DuplicateIdentifer("duplicate member '" + m.name() + "' added");
	}

	mMembers.insert(std::make_pair<std::string, Object>(m.name(), m));
}

void Object::addMethod(Method m)
{
	os_debug("addMethod(" + m.name() + ", [" + toString(m.provideSignature()) + "])");

	if ( mMethods.find(m) != mMethods.end() ) {
		throw DuplicateIdentifer("duplicate method '" + m.name() + "' added with same signature");
	}

	mMethods.insert(m);
}

void Object::addParent(const std::string& parent)
{
	for ( StringList::const_iterator it = mParents.begin(); it != mParents.end(); ++it ) {
		if ( (*it) == parent ) {
			throw Exception("duplicate inheritance detected");
		}
	}

	mParents.push_back(parent);
}

void Object::assign(const Object& other)
{
	if ( other.mConstructed )	// don't override this with false
		this->mConstructed = other.mConstructed;
	this->mMembers = other.mMembers;
	this->mMethods = other.mMethods;
	this->mTokens = other.mTokens;
	this->mType = other.mType;
	this->mValue = other.mValue;

	updateMethodOwners();
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

void Object::Constructor(const VariablesList& params)
{
	if ( mConstructed ) {
		throw Exception("can not construct object '" + name() + "' multiple times");
	}

	updateMethodOwners();

	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		it->second = mRepository->createInstance(it->second.type(), it->second.name());
		it->second.connectPrinter(mPrinter);
		it->second.connectRepository(mRepository);
		it->second.Constructor(VariablesList());
	}

	// only execute constructor if one is present
	if ( hasMethod(type(), params) ) {
		execute(type(), params);
	}

	// set after executing constructor
	// in case any exceptions have been thrown
	mConstructed = true;
}

void Object::Destructor()
{
	if ( !mConstructed ) {
		// either the destructor has already been executed (successfully)
		// or the constructor has never been called successfully!
		throw Exception("can not destroy object '" + name() + "' which has not been constructed");
	}

	// only execute destructor if one is present
	if ( hasMethod("~" + mName) ) {
		execute("~" + mName, VariablesList());
	}

	garbageCollector();

	// set after executing destructor
	// in case any exceptions have been thrown
	mConstructed = false;
}

Object Object::execute(const std::string& method, const VariablesList& params, const Method* caller)
{
	os_debug("execute('" + method + "', [" + toString(params) + "])");

	MethodCollection::iterator mIt;
	bool success = findMethod(method, params, mIt);
	if ( !success ) {
		throw UnknownIdentifer("unknown method '" + method + "' or method with invalid parameter count called!");
	}

	// are we called from a member function?
	bool callFromMember = false;
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( caller && (*it) == *caller ) {
			// we have been called from a member function/method
			// so visibility does not matter
			callFromMember = true;
			break;
		}
	}

	// check visibility:
	// member functions can always call us,
	// for calls from non-member functions the method visibility must be public
	if ( !callFromMember && mIt->visibility() != Visibility::Public ) {
		throw VisibilityError("invalid visibility: " + method);
	}

	Object returnValue(name(), "", type(), "");
	returnValue.visibility(visibility());
	try {
		// execute our member method
		returnValue.assign(mIt->execute(params));
	}
	catch ( Exception &e ) {
		// catch and log all errors that occured during method execution
		std::cout << e.what() << std::endl;
	}

	return returnValue;
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
			return it->second.findMember(member, mIt);
		}
	}

	return false;
}

bool Object::findMember_(const std::string& m, Object::MemberCollection::iterator& mIt)
{
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == m ) {
			mIt = it;
			return true;
		}
	}

	std::string member, parent;
	Tools::split(m, parent, member);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == parent ) {
			return it->second.findMember(member, mIt);
		}
	}

	return false;
}

bool Object::findMethod(const std::string& m, MethodCollection::iterator& mIt)
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( it->name() == m /*&& it->visibility() == Visibility::Public*/ ) {
			mIt = it;
			return true;
		}
	}

	std::string method, parent;
	Tools::split(m, parent, method);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == parent ) {
			return it->second.findMethod(method, mIt);
		}
	}

	return false;
}

bool Object::findMethod_(const std::string& m, MethodCollection::iterator& mIt)
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( it->name() == m ) {
			mIt = it;
			return true;
		}
	}

	std::string method, parent;
	Tools::split(m, parent, method);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == parent ) {
			return it->second.findMethod(method, mIt);
		}
	}

	return false;
}

bool Object::findMethod(const std::string& m, const VariablesList& params, MethodCollection::iterator& mIt)
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( it->name() == m && it->isSignatureValid(params) /*&& it->visibility() == Visibility::Public*/ ) {
			mIt = it;
			return true;
		}
	}

	std::string method, parent;
	Tools::split(m, parent, method);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == parent ) {
			return it->second.findMethod(method, params, mIt);
		}
	}

	return false;
}

bool Object::findMethod_(const std::string& m, const VariablesList& params, MethodCollection::iterator& mIt)
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( it->name() == m && it->isSignatureValid(params) ) {
			mIt = it;
			return true;
		}
	}

	std::string method, parent;
	Tools::split(m, parent, method);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == parent ) {
			return it->second.findMethod(method, params, mIt);
		}
	}

	return false;
}

void Object::garbageCollector()
{
	// clean up all members (= reset to zero/empty)
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		it->second.value("");
	}
	mMembers.clear();

	mMethods.clear();
}

Object& Object::getMember(const std::string& m)
{
	std::string member, parent;
	Tools::split(m, parent, member);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == m ) {
			return it->second;
		}

		if ( !it->second.isValid() ) {
			throw Exception("trying to access not yet constructed object '" + this->name() + "'!");
		}

		if ( it->second.name() == parent ) {
			return it->second.getMember(member);
		}
	}

	throw UnknownIdentifer(m);
}

bool Object::hasMember(const std::string& m)
{
	std::string member, parent;
	Tools::split(m, parent, member);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == m ) {
			return true;
		}

		if ( it->second.name() == parent ) {
			if ( it->second.hasMember(member) ) {
				return true;
			}
		}
	}

	return false;
}

bool Object::hasMethod(const std::string& m)
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( it->name() == m ) {
			return true;
		}
	}

	std::string method, parent;
	Tools::split(m, parent, method);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == parent ) {
			if ( it->second.hasMethod(method) ) {
				return true;
			}
		}
	}

	return false;
}

bool Object::hasMethod(const std::string& m, const VariablesList& params)
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( it->name() == m && it->isSignatureValid(params) ) {
			return true;
		}
	}

	std::string method, parent;
	Tools::split(m, parent, method);

	// loop through all members and ask them if this identifier belongs to them
	for ( MemberCollection::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->first == parent ) {
			if ( it->second.hasMethod(method, params) ) {
				return true;
			}
		}
	}

	return false;
}

bool Object::isValid() const
{
	return mConstructed;
}

IPrinter* Object::providePrinter() const
{
	return mPrinter;
}

void Object::updateMethodOwners()
{
	for ( MethodCollection::iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		it->setOwner(this);
		it->setRepository(mRepository);
	}
}


}
