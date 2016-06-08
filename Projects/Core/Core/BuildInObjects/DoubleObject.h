
#ifndef Core_Runtime_BuildInObjects_DoubleObject_h
#define Core_Runtime_BuildInObjects_DoubleObject_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class DoubleObject : public Object
{
public:
	static double DEFAULTVALUE;
	static AtomicValue ATOMIC_DEFAULTVALUE;
	static std::string TYPENAME;

public:
	DoubleObject(AtomicValue value = 0.0);
	DoubleObject(const std::string& name, double value);
	DoubleObject(const Object& object);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public:	// Operators
	virtual void operator_assign(DoubleObject *other);
	virtual void operator_assign(const Object *other);

	virtual bool operator_bool() const;

	virtual void operator_divide(DoubleObject *other);
	virtual void operator_divide(Object *other);

	virtual bool operator_equal(DoubleObject *other) const;
	virtual bool operator_equal(Object *other) const;

	virtual bool operator_greater(DoubleObject *other) const;
	virtual bool operator_greater(Object *other) const;

	virtual bool operator_greater_equal(DoubleObject *other) const;
	virtual bool operator_greater_equal(Object *other) const;

	virtual bool operator_less(DoubleObject *other) const;
	virtual bool operator_less(Object *other) const;

	virtual bool operator_less_equal(DoubleObject *other) const;
	virtual bool operator_less_equal(Object *other) const;

	virtual void operator_multiply(DoubleObject *other);
	virtual void operator_multiply(Object *other);

	virtual void operator_plus(DoubleObject *other);
	virtual void operator_plus(Object *other);

	virtual void operator_subtract(DoubleObject *other);
	virtual void operator_subtract(Object *other);

	virtual void operator_unary_decrement();
	virtual void operator_unary_increment();
	virtual void operator_unary_minus();
	virtual void operator_unary_not();

public: // Values
	virtual bool isValid() const;

	virtual std::string ToString() const;

protected:

private:

};


}
}


#endif
