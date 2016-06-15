
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
	virtual void operator_assign(const DoubleObject *other);
	virtual void operator_assign(const Object *other);

	virtual bool operator_bool() const;

	virtual void operator_divide(const DoubleObject *other);
	virtual void operator_divide(const Object *other);

	virtual bool operator_equal(const DoubleObject *other);
	virtual bool operator_equal(const Object *other);

	virtual bool operator_greater(const DoubleObject *other);
	virtual bool operator_greater(const Object *other);

	virtual bool operator_greater_equal(const DoubleObject *other);
	virtual bool operator_greater_equal(const Object *other);

	virtual bool operator_less(const DoubleObject *other);
	virtual bool operator_less(const Object *other);

	virtual bool operator_less_equal(const DoubleObject *other);
	virtual bool operator_less_equal(const Object *other);

	virtual void operator_multiply(const DoubleObject *other);
	virtual void operator_multiply(const Object *other);

	virtual void operator_plus(const DoubleObject *other);
	virtual void operator_plus(const Object *other);

	virtual void operator_subtract(const DoubleObject *other);
	virtual void operator_subtract(const Object *other);

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
