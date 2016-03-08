
#ifndef ObjectiveScript_Object_h
#define ObjectiveScript_Object_h


// Library includes
#include <cassert>
#include <map>
#include <string>

// Project includes
#include <Core/Attributes/Attributes.h>
#include <Core/Designtime/Ancestor.h>
#include <Core/Designtime/BluePrint.h>
#include <Core/Runtime/ControlFlow.h>
#include "Interpreter.h"
#include "Method.h"
#include "Parameter.h"
#include "Scope.h"
#include "Symbol.h"
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


class Object : public ObjectScope,
			   public ObjectSymbol
{
public:
	Object();
	Object(const std::string& name, const std::string& filename, const std::string& type, const std::string& value);
	Object(const Object& other);
	virtual ~Object();

public:
	void operator= (const Object& other);

public:	// Symbol::IType implementation & RTTI
	const std::string& Filename() const {
		return mFilename;
	}
	const std::string& Typename() const {
		return mTypename;
	}

	void overrideTypename(const std::string& type) {
		mTypename = type;
	}

public:	// Setup
	void addInheritance(const Designtime::Ancestor& ancestor, Object* inheritance);
	void setRepository(Repository *repository);

public: // Symbol
	Symbol* resolve(const std::string& name, bool onlyCurrentScope) const;
	ObjectiveScript::MethodSymbol* resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope) const;

public:	// Value
	virtual std::string getValue() const;
	virtual void setValue(const std::string& value);

	virtual bool isAtomicType() const;
	virtual bool isValid() const;
	virtual std::string ToString() const;

public:	// Usage
	ControlFlow::E Constructor(const ParameterList& params);
	ControlFlow::E Destructor();
	ControlFlow::E execute(Object *result, const std::string& method, const ParameterList& params, const Method* caller = 0);		// throws VisibilityError exception

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

protected:
	typedef std::map<Designtime::Ancestor, Object*> Inheritance;

protected:
	void garbageCollector();

protected:
	//std::string mCurrentOuterface;
	std::string mFilename;
	Inheritance mInheritance;
	bool mIsAtomicType;
	bool mIsConstructed;
	Repository *mRepository;
	Object *mThis;
	std::string mTypename;
	std::string mValue;

private:
};


}
}


#endif
