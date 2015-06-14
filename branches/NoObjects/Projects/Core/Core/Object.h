
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
#include "Scope.h"
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
class Object;
class Repository;


class Object : public LocalScope,
			   public BluePrint
{
public:
	Object();
	Object(const std::string& name, const std::string& filename);
	Object(const std::string& name, const std::string& filename, const std::string& type, const std::string& value);
	virtual ~Object();

public:
	void operator= (const Object& other);

public:	// Setup
	void addMember(Object *m);		// throws DuplicateIdentifer exception
	void addMethod(Method *m);		// throws DuplicateIdentifer exception
	void addParent(const std::string& parent);

public:	// Connectors
	void connectPrinter(IPrinter *p);
	void connectRepository(Repository *r);

public:	// Providers
	IPrinter* providePrinter() const;

public:	// Operators
	virtual void operator_assign(Object *other);
	virtual void operator_divide(Object *other);
	virtual void operator_multiply(Object *other);
	virtual void operator_plus(Object *other);
	virtual void operator_subtract(Object *other);

	virtual std::string ToString() const;

public:
	const std::string& name() const;
	void name(const std::string& name);

	const std::string& value() const;
	void value(const std::string& value);

public:	// Usage
	void Constructor(const ParameterList& params);
	void Destructor();
	void garbageCollector(bool force = false);

	void execute(Object *result, const std::string& method, const ParameterList& params, const Method* caller = 0);		// throws VisibilityError exception

public:	// Helpers
	Object* getMember(const std::string& m);
	bool hasMember(const std::string& m);
	bool hasMethod(const std::string& m);
	bool hasMethod(const std::string& m, const ParameterList& params);

	bool isValid() const;

protected:

private:
	typedef std::map<std::string, Object*> MemberCollection;
	typedef std::set<Method*> MethodCollection;

private:
	bool findMember(const std::string& m, MemberCollection::iterator& mIt);
	bool findMethod(const std::string& m, MethodCollection::iterator& mIt);
	bool findMethod(const std::string& m, const ParameterList& params, MethodCollection::iterator& mIt);

private:
	void updateMethodOwners();

private:
	bool mConstructed;
	MemberCollection mMembers;
	MethodCollection mMethods;
	std::string mName;
	StringList mParents;
	IPrinter *mPrinter;
	Repository *mRepository;
	std::string mValue;
};

typedef std::list<Object> ObjectList;


}


#endif
