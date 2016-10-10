
#ifndef ObjectiveScript_Core_Object_h
#define ObjectiveScript_Core_Object_h


// Library includes
#include <cassert>
#include <map>
#include <string>
#include <Json/Value.h>

// Project includes
#include <Core/Attributes/Attributes.h>
#include <Core/Designtime/Ancestor.h>
#include <Core/Designtime/BluePrintObject.h>
#include <Core/Runtime/AtomicValue.h>
#include <Core/Runtime/ControlFlow.h>
#include "Interpreter.h"
#include "Method.h"
#include "Parameter.h"
#include "Reference.h"
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


class Object : public MethodScope,
			   public ObjectSymbol
{
public:
	Object();
	Object(const std::string& name, const std::string& filename, const std::string& type, AtomicValue value);
	Object(const Object& other);
	virtual ~Object();

public:
	void operator= (const Object& other);
	void assign(const Object& other);
	void assignSubType(const Object& other);
	void copy(const Object& other);

public:	// Symbol::IType implementation & RTTI
	const std::string& Filename() const { return mFilename; }
	const std::string& Outterface() const { return mOutterface; }
	const std::string& QualifiedOutterface() const { return mQualifiedOutterface; }
	const std::string& QualifiedTypename() const { return mQualifiedTypename; }
	const std::string& Typename() const { return mTypename; }

	void setOutterface(const std::string& type) { mOutterface = type; }
	void setQualifiedOutterface(const std::string& type) { mQualifiedOutterface = type; }
	void setQualifiedTypename(const std::string& type) { mQualifiedTypename = type; }
	void setTypename(const std::string &type) { mTypename = type; }

public:	// Setup
	void addInheritance(const Designtime::Ancestor& ancestor, Object* inheritance);
	void setConstructed(bool state);
	void setParent(IScope *scope);

public:	// Reference
	const Reference& getReference() const { return mReference; }
	void setReference(const Reference& reference) { mReference = reference; }

public: // Symbol
	Symbol* resolve(const std::string& name, bool onlyCurrentScope) const;
	ObjectiveScript::MethodSymbol* resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope) const;

public:	// Type
	bool isInstanceOf(const std::string& type) const;

public:	// Value
	virtual AtomicValue getValue() const;
	virtual void setValue(AtomicValue value);

	virtual bool isAbstract() const;
	virtual bool isArray() const;
	virtual bool isAtomicType() const;
	virtual bool isValid() const;

	virtual void setArray(bool value, size_t size = 0);
	virtual std::string ToString(unsigned int indent = 0) const;

public:	// Json serialization
	virtual bool FromJson(const Json::Value& value);
	virtual Json::Value ToJson() const;

public:	// Usage
	bool CanExecuteDefaultConstructor() const;
	ControlFlow::E Constructor(const ParameterList& params);
	ControlFlow::E Destructor();
	ControlFlow::E execute(Object *result, const std::string& method, const ParameterList& params, const Method* caller = 0);		// throws VisibilityError exception

public:	// Operators
	virtual const Object* operator_array(const Object *index);
	virtual void operator_assign(const Object *other);
	virtual void operator_bitand(const Object *other);
	virtual void operator_bitcomplement(const Object *other);
	virtual void operator_bitor(const Object *other);
	virtual bool operator_bool() const;
	virtual void operator_divide(const Object *other);
	virtual bool operator_equal(const Object *other);
	virtual bool operator_greater(const Object *other);
	virtual bool operator_greater_equal(const Object *other);
	virtual bool operator_is(const Symbol *other);
	virtual bool operator_less(const Object *other);
	virtual bool operator_less_equal(const Object *other);
	virtual void operator_modulo(const Object *other);
	virtual void operator_multiply(const Object *other);
	virtual void operator_plus(const Object *other);
	virtual void operator_subtract(const Object *other);
	virtual void operator_unary_decrement();
	virtual void operator_unary_increment();
	virtual void operator_unary_minus();
	virtual void operator_unary_not();

protected:
	typedef std::map<Designtime::Ancestor, Object*> Inheritance;

protected:
	void garbageCollector();

protected:
	std::string mFilename;
	Inheritance mInheritance;
	bool mIsArray;
	bool mIsArrayDynamicallyExpanding;
	bool mIsAtomicType;
	bool mIsConstructed;
	std::string mOutterface;
	std::string mQualifiedOutterface;
	std::string mQualifiedTypename;
	Reference mReference;
	std::string mTypename;
	AtomicValue mValue;

private:
};


}
}


#endif
