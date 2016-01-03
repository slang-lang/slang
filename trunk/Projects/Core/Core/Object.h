
#ifndef ObjectiveScript_Object_h
#define ObjectiveScript_Object_h


// Library includes
#include <map>
#include <string>
#include <set>

// Project includes
#include <Core/Attributes/Attributes.h>
#include "BluePrint.h"
#include "Method.h"
#include "Parameter.h"
#include "Scope.h"
#include "Token.h"
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class BoolObject;
class FloatObject;
class IntegerObject;
class NumberObject;
class StringObject;
class VoidObject;

// Forward declarations
class IPrinter;
class Method;
class Object;
class Repository;


class Object : public LocalScope,
			   public ObjectSymbol,
			   public BluePrint
{
public:
	Object();
	Object(const std::string& name, const std::string& filename);
	Object(const std::string& name, const std::string& filename, const std::string& type, const std::string& value);
	Object(const Object& other);
	virtual ~Object();

public:
	Object& operator= (const Object& other);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public:	// Setup
	void addMember(Object *m);		// throws DuplicateIdentifer exception
	void addMethod(Method *m);		// throws DuplicateIdentifer exception
	void addParent(const std::string& parent);

public:	// Connectors
	void connectRepository(Repository *r);

public:	// Operators
	virtual void operator_assign(Object *other);
	virtual void operator_bitand(Object *other);
	virtual void operator_bitor(Object *other);
	virtual void operator_divide(Object *other);
	virtual bool operator_equal(Object *other);
	virtual bool operator_greater(Object *other);
	virtual bool operator_greater_equal(Object *other);
	virtual bool operator_less(Object *other);
	virtual bool operator_less_equal(Object *other);
	virtual void operator_modulo(Object *other);
	virtual void operator_multiply(Object *other);
	virtual void operator_plus(Object *other);
	virtual void operator_subtract(Object *other);

public:	// Value
	virtual bool isValid() const;

	virtual std::string ToString() const;

public:
	bool isAtomicType() const;

	void overrideName(const std::string& /*name*/) {
		//mName = name;
	}
	void overrideType(const std::string& type) {
		mTypename = type;
	}

	virtual std::string getValue() const;
	virtual void setValue(const std::string& value);

public:	// Usage
	void Constructor(const ParameterList& params);
	void Destructor();
	void execute(Object *result, const std::string& method, const ParameterList& params, const Method* caller = 0);		// throws VisibilityError exception
	void garbageCollector(bool force = false);

public:	// Helpers
	Object* getMember(const std::string& m) const;
	bool hasMethod(const std::string& m) const;
	bool hasMethod(const std::string& m, const ParameterList& params) const;

protected:
	bool mIsAtomicType;
	Repository *mRepository;

private:
	typedef std::map<std::string, Object*> MemberCollection;
	typedef std::set<Method*> MethodCollection;

private:
	void copyMember(Object *member);
	bool findMember(const std::string& m, MemberCollection::const_iterator& mIt) const;
	bool findMethod(const std::string& m, MethodCollection::const_iterator& mIt) const;
	bool findMethod(const std::string& m, const ParameterList& params, MethodCollection::const_iterator& mIt) const;

private:
	bool mConstructed;
	MemberCollection mMembers;
	MethodCollection mMethods;
	StringList mParents;
	std::string mValue;
};

typedef std::list<Object> ObjectList;


}


#endif
