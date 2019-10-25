
#ifndef ObjectiveScript_Core_Object_h
#define ObjectiveScript_Core_Object_h


// Library includes
#include <cassert>
#include <map>
#include <string>

// Project includes
#include <Core/Attributes/Attributes.h>
#include <Core/Designtime/Ancestor.h>
#include <Core/Designtime/BluePrintObject.h>
#include <Core/Designtime/Parser/Token.h>
#include <Core/Runtime/AtomicValue.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/Runtime/Reference.h>
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
			   public ObjectSymbol
{
public:
	Object();
	Object(const std::string& name, const std::string& filename, const std::string& type, AtomicValue value);
	virtual ~Object();

public:
	Object& operator= (const Object& other);
	void assign(const Object& other);

public: // MethodScope overrides
	void defineMember(const std::string& name, Symbol* symbol);
	void defineMethod(const std::string& name, Common::Method* method);

public:	// Symbol::IType implementation & RTTI
	const std::string& Filename() const { return mFilename; }
	const std::string& QualifiedOuterface() const { return mQualifiedOuterface; }
	const std::string& QualifiedTypename() const { return mQualifiedTypename; }

	void setQualifiedOuterface(const std::string &type) { mQualifiedOuterface = type; }

public:	// Setup
	void addInheritance(const Designtime::Ancestor& ancestor, Object* inheritance);

	void setIsReference(bool state);
	void setParent(IScope *scope);

	Designtime::BluePrintObject* getBluePrint() const;
	void setBluePrint(Designtime::BluePrintObject* blueprint);

public:	// Reference
	const Reference& getReference() const;
	void setReference(const Reference& reference);

public: // Symbol
	Symbol* resolve(const std::string& name, bool onlyCurrentScope, Visibility::E visibility) const;
	ObjectiveScript::MethodSymbol* resolveMethod(const std::string& name, const ParameterList& params, bool onlyCurrentScope, Visibility::E visibility) const;

public:	// Type
	bool isInstanceOf(const std::string& type) const;

public:	// Value
	AtomicValue getValue() const;
	void setValue(AtomicValue value);

	Object* getThis() const { return mThis; }

	bool isAbstract() const;
	bool isAtomicType() const;
	bool isEnumerationValue() const;
	virtual bool isValid() const;

	virtual std::string ToString(unsigned int indent = 0) const;

public:	// Usage
	bool CanExecuteDefaultConstructor() const;
	ControlFlow::E Constructor(const ParameterList& params);
	ControlFlow::E Destructor();
	ControlFlow::E execute(Object *result, const std::string& method, const ParameterList& params);

public:	// Operators
	virtual void operator_assign(const Object *other);
	virtual void operator_bitand(const Object *other);
	virtual void operator_bitcomplement(const Object *other);
	virtual void operator_bitor(const Object *other);
	virtual bool operator_bool() const;
	virtual void operator_divide(const Object *other);
	virtual bool operator_equal(const Object *other);
	virtual bool operator_greater(const Object *other);
	virtual bool operator_greater_equal(const Object *other);
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
	virtual void operator_unary_plus();

protected:
	typedef std::map<Designtime::Ancestor, Object*> Inheritance;

protected:
	void deinit();
	void garbageCollector();

protected:
	Designtime::BluePrintObject* mBluePrint;
	std::string mFilename;
	Inheritance mInheritance;
	bool mIsAtomicType;
	bool mIsReference;
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
