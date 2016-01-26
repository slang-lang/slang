
#ifndef ObjectiveScript_Object_h
#define ObjectiveScript_Object_h


// Library includes
#include <cassert>
#include <map>
#include <string>
#include <set>

// Project includes
#include <Core/Attributes/Attributes.h>
#include "BluePrint.h"
#include "Interpreter.h"
#include "Method.h"
#include "Parameter.h"
#include "Scope.h"
#include "Token.h"
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declaration
class IPrinter;
class Repository;

namespace Runtime {

// Forward declarations
class BoolObject;
class FloatObject;
class IntegerObject;
class NumberObject;
class StringObject;
class VoidObject;

// Forward declarations
class Method;
class Object;


class Object : public MethodScope,
			   public ObjectSymbol,
			   public RTTI
{
public:
	Object();
	Object(const std::string& name, const std::string& filename, const std::string& type, const std::string& value);
	Object(const Object& other);
	virtual ~Object();

public:
	void operator= (const Object& other);

public:	// Symbol::IType implementation
	virtual const std::string& getTypeName() const;

public:	// Setup
	void setRepository(Repository *repository);

public:	// Operators
	virtual void operator_assign(Object *other);
	virtual void operator_bitand(Object *other);
	virtual void operator_bitcomplement(Object *other);
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
	virtual void operator_unary_decrement();
	virtual void operator_unary_increment();
	virtual void operator_unary_minus();
	virtual void operator_unary_not();

public:	// Value
	void overrideType(const std::string& type) {
		mTypename = type;
	}

	virtual std::string getValue() const;
	virtual void setValue(const std::string& value);

	virtual bool isAtomicType() const;
	virtual bool isValid() const;
	virtual std::string ToString() const;

public:	// Usage
	void Constructor(const ParameterList& params);
	void Destructor();
	ControlFlow::E execute(Object *result, const std::string& method, const ParameterList& params, const Method* caller = 0);		// throws VisibilityError exception
	void garbageCollector();

protected:
	bool mIsAtomicType;
	Repository *mRepository;
	std::string mValue;

private:
	bool mConstructed;
};


}
}


#endif
