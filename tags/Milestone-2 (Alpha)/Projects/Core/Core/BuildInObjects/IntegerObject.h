
#ifndef Core_Runtime_BuildInObjects_IntegerObject_h
#define Core_Runtime_BuildInObjects_IntegerObject_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class IntegerObject : public Object
{
public:
	static AtomicValue DEFAULTVALUE;
	static std::string TYPENAME;

public:
	IntegerObject(AtomicValue value = DEFAULTVALUE);
	IntegerObject(const std::string& name, int value);
	IntegerObject(const Object& object);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public:	// Operators
	virtual void operator_assign(const IntegerObject *other);
	virtual void operator_assign(const Object *other);

	virtual bool operator_bool() const;

	virtual void operator_divide(const IntegerObject *other);
	virtual void operator_divide(const Object *other);

	virtual bool operator_equal(const IntegerObject *other);
	virtual bool operator_equal(const Object *other);

	virtual bool operator_greater(const IntegerObject *other);
	virtual bool operator_greater(const Object *other);

	virtual bool operator_greater_equal(const IntegerObject *other);
	virtual bool operator_greater_equal(const Object *other);

	virtual bool operator_less(const IntegerObject *other);
	virtual bool operator_less(const Object *other);

	virtual bool operator_less_equal(const IntegerObject *other);
	virtual bool operator_less_equal(const Object *other);

	virtual void operator_modulo(const IntegerObject *other);
	virtual void operator_modulo(const Object *other);

	virtual void operator_multiply(const IntegerObject *other);
	virtual void operator_multiply(const Object *other);

	virtual void operator_plus(const IntegerObject *other);
	virtual void operator_plus(const Object *other);

	virtual void operator_subtract(const IntegerObject *other);
	virtual void operator_subtract(const Object *other);

	virtual void operator_unary_decrement();
	virtual void operator_unary_increment();
	virtual void operator_unary_minus();
	virtual void operator_unary_not();

public: // Values
	virtual bool isValid() const;

	virtual std::string ToString(unsigned int indent) const;

protected:

private:

};


}
}


#endif