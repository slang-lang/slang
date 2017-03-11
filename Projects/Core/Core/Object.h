
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
#include <Core/Designtime/Parser/Token.h>
#include <Core/Interfaces/IRuntimeType.h>
#include <Core/Runtime/AtomicValue.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/Runtime/Reference.h>
#include "Interpreter.h"
#include "Parameter.h"
#include "Scope.h"
#include "Symbol.h"
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declaration
class Repository;

namespace Runtime {

// Forward declarations
class Method;

class Object : public MethodScope,
			   public ObjectSymbol,
			   public IRuntimeType
{
public:
	Object();
	Object(const std::string& name, const std::string& filename, const std::string& type, AtomicValue value);
	Object(const Object& other);
	virtual ~Object();

public:
	Object& operator= (const Object& other);
	void assign(const Object& other, bool overrideType = false);
	void copy(const Object& other);

public: // MethodScope overrides
	void defineMember(const std::string& name, Symbol* symbol);
	void defineMethod(const std::string& name, Common::Method* method);

public:	// Symbol::IType implementation & RTTI
	const std::string& Filename() const { return mFilename; }
	const std::string& QualifiedOuterface() const { return mQualifiedOuterface; }
	const std::string& QualifiedTypename() const { return mQualifiedTypename; }

	void setQualifiedOuterface(const std::string &type) { mQualifiedOuterface = type; }

public: // IRuntimeType implementation
	void initialize();

public:	// Setup
	void addInheritance(const Designtime::Ancestor& ancestor, Object* inheritance);
	void setConstructed(bool state);
	void setParent(IScope *scope);

	Designtime::BluePrintObject* getBluePrint() const;
	void setBluePrint(Designtime::BluePrintObject* blueprint);

public:	// Reference
	const Reference& getReference() const { return mReference; }
	void setReference(const Reference& reference) { mReference = reference; }

public: // Symbol
	Symbol* resolve(const std::string& name, bool onlyCurrentScope, Visibility::E visibility) const;
	ObjectiveScript::MethodSymbol* resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope, Visibility::E visibility) const;

public:	// Type
	bool isInstanceOf(const std::string& type) const;

public:	// Value
	AtomicValue getValue() const;
	void setValue(AtomicValue value);

	bool isAbstract() const;
	bool isAtomicType() const;
	bool isConstructed() const;
	bool isNull() const;
	bool isValid() const;

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
	virtual void operator_array(const Object *index, Object* result);
	virtual void operator_assign(const Object *other);
	virtual void operator_bitand(const Object *other);
	virtual void operator_bitcomplement(const Object *other);
	virtual void operator_bitor(const Object *other);
	virtual bool operator_bool() const;
	virtual void operator_divide(const Object *other);
	virtual bool operator_equal(const Object *other);
	virtual bool operator_greater(const Object *other);
	virtual bool operator_greater_equal(const Object *other);
	virtual bool operator_is(const std::string& type);
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
	Object* mBase;
	Designtime::BluePrintObject* mBluePrint;
	std::string mFilename;
	Inheritance mInheritance;
	bool mIsAtomicType;
	bool mIsConstructed;
	bool mIsNull;
	std::string mQualifiedOuterface;
	std::string mQualifiedTypename;
	Reference mReference;
	Object* mThis;
	std::string mTypename;
	AtomicValue mValue;

private:
	void assignReference(const Reference& ref);
};


}
}


#endif
