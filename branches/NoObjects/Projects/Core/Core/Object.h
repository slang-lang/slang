
#ifndef ObjectiveScript_Object_h
#define ObjectiveScript_Object_h


// Library includes
#include <map>
#include <set>

// Project includes
#include <Core/Attributes/Attributes.h>
#include "BluePrint.h"
#include "Method.h"
#include "Parameter.h"
#include "Token.h"
#include "Types.h"
#include "Variable.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IPrinter;
class Memory;
class Method;
class Repository;


class Object : public BluePrint,
			   public Variable/*,
			   public Attributes*/
{
public:
	Object();
	Object(const std::string& name, const std::string& filename);
	Object(const std::string& name, const std::string& filename, const std::string& type, const std::string& value);
	Object(const Variable& var);
	~Object();

public:	// Setup
	void addMember(Object m);		// throws DuplicateIdentifer exception
	void addMethod(Method m);		// throws DuplicateIdentifer exception
	void addParent(const std::string& parent);

public:	// Connectors
	void connectMemory(Memory *m);
	void connectPrinter(IPrinter *p);
	void connectRepository(Repository *r);

public:	// Providers
	IPrinter* providePrinter() const;

public:	// Usage
	void assign(Object other); //void assign(const Object& other);
	void Constructor(const ParameterList& params);
	void Destructor();

	Variable execute(const std::string& method, const ParameterList& params, const Method* caller = 0);		// throws VisibilityError exception

public:	// Helpers
	Object& getMember(const std::string& m);		// throws UnknownIdentifer exception
	bool hasMember(const std::string& m);
	bool hasMethod(const std::string& m);
	bool hasMethod(const std::string& m, const ParameterList& params);

	bool isValid() const;

protected:

private:
	typedef std::map<std::string, Object> MemberCollection;
	typedef std::set<Method> MethodCollection;

private:
	bool findMember(const std::string& m, MemberCollection::iterator& mIt);
	bool findMethod(const std::string& m, MethodCollection::iterator& mIt);
	bool findMethod(const std::string& m, const ParameterList& params, MethodCollection::iterator& mIt);

	bool findMember_(const std::string& m, MemberCollection::iterator& mIt);
	bool findMethod_(const std::string& m, MethodCollection::iterator& mIt);
	bool findMethod_(const std::string& m, const ParameterList& params, MethodCollection::iterator& mIt);

private:
	void garbageCollector();
	void updateMethodOwners();

private:
	bool				mConstructed;
	MemberCollection	mMembers;
	Memory				*mMemory;
	MethodCollection	mMethods;
	StringList			mParents;
	IPrinter			*mPrinter;
	Repository			*mRepository;
};

typedef std::list<Object> ObjectList;


}


#endif
