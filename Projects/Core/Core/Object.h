
#ifndef ObjectiveScript_Object_h
#define ObjectiveScript_Object_h


// Library includes
#include <map>
#include <set>

// Project includes
#include "Method.h"
#include "Token.h"
#include "Types.h"
#include "Variable.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IPrinter;
class Method;
class Repository;

class ObjectBluePrint
{
public:
	class Ancestor
	{
	public:
		Ancestor(const std::string& name, Visibility::E visibility)
		: mName(name),
		  mVisibility(visibility)
		{ }

	public:
		const std::string& name() const {
			return mName;
		}
		Visibility::E visibility() const {
			return mVisibility;
		}

	protected:

	private:
		std::string	mName;
		Visibility::E mVisibility;
	};

	typedef std::map<std::string, Ancestor> Ancestors;

public:
	ObjectBluePrint()
	{ }

	ObjectBluePrint(const std::string& objectType, const std::string& filename)
	: mFilename(filename),
	  mObjectType(objectType),
	  mVisibility(Visibility::Public)
	{ }

public:
	const Ancestors& getAncestors() const {
		return mAncestors;
	}
	void setAncestors(const Ancestors& ancestors) {
		mAncestors = ancestors;
	}

	const TokenList& getTokens() const {
		return mTokens;
	}
	virtual void setTokens(const TokenList& tokens) {
		mTokens = tokens;
	}

	Visibility::E getVisibility() const {
		return mVisibility;
	}
	void setVisibility(Visibility::E v) {
		mVisibility = v;
	}

public:
	const std::string& filename() const {
		return mFilename;
	}
	const std::string& objectType() const {
		return mObjectType;
	}

protected:
	Ancestors		mAncestors;
	std::string		mObjectType;
	TokenList		mTokens;
	Visibility::E	mVisibility;

private:
	std::string		mFilename;
};


class Object : public ObjectBluePrint,
			   public Variable
{
public:
	Object();
	Object(const std::string& name, const std::string& filename);
	Object(const std::string& name, const std::string& filename, const std::string& type, const std::string& value);
	~Object();

public:	// Setup
	void addMember(Object m);		// throws DuplicateIdentifer exception
	void addMethod(Method m);		// throws DuplicateIdentifer exception
	void addParent(const std::string& parent);

public:	// Connectors
	void connectPrinter(IPrinter *p);
	void connectRepository(Repository *r);

public:	// Providers
	IPrinter* providePrinter() const;

public:	// Usage
	void assign(const Object& other);
	void Constructor(const VariablesList& params);
	void Destructor();

	Object execute(const std::string& method, const VariablesList& params, const Method* caller = 0);		// throws VisibilityError exception

public:	// Helpers
	Object& getMember(const std::string& m);		// throws UnknownIdentifer exxception
	bool hasMember(const std::string& m);
	bool hasMethod(const std::string& m);
	bool hasMethod(const std::string& m, const VariablesList& params);

	bool isValid() const;

protected:

private:
	typedef std::map<std::string, Object> MemberCollection;
	typedef std::set<Method> MethodCollection;

private:
	bool findMember(const std::string& m, MemberCollection::iterator& mIt);
	bool findMethod(const std::string& m, MethodCollection::iterator& mIt);
	bool findMethod(const std::string& m, const VariablesList& params, MethodCollection::iterator& mIt);

	bool findMember_(const std::string& m, MemberCollection::iterator& mIt);
	bool findMethod_(const std::string& m, MethodCollection::iterator& mIt);
	bool findMethod_(const std::string& m, const VariablesList& params, MethodCollection::iterator& mIt);

private:
	void garbageCollector();
	void updateMethodOwners();

private:
	bool				mConstructed;
	MemberCollection	mMembers;
	MethodCollection	mMethods;
	StringList			mParents;
	IPrinter			*mPrinter;
	Repository			*mRepository;
};

typedef std::list<ObjectBluePrint> ObjectBluePrintList;
typedef std::list<Object> ObjectList;


}


#endif
