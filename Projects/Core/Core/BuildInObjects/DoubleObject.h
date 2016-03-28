
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
	static std::string TYPENAME;

public:
	DoubleObject(double value = 0.0);
	DoubleObject(const std::string& name, double value);
	DoubleObject(const Object& object);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public:	// Operators
	virtual operator bool() const;

	virtual void operator_assign(DoubleObject *other);
	virtual void operator_assign(Object *other);

	virtual void operator_divide(DoubleObject *other);
	virtual void operator_divide(Object *other);

	virtual bool operator_equal(DoubleObject *other);
	virtual bool operator_equal(Object *other);

	virtual bool operator_greater(DoubleObject *other);
	virtual bool operator_greater(Object *other);

	virtual bool operator_greater_equal(DoubleObject *other);
	virtual bool operator_greater_equal(Object *other);

	virtual bool operator_less(DoubleObject *other);
	virtual bool operator_less(Object *other);

	virtual bool operator_less_equal(DoubleObject *other);
	virtual bool operator_less_equal(Object *other);

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
	virtual double getNativeValue() const;
	virtual void setNativeValue(double value);

	virtual std::string getValue() const;
	virtual void setValue(const std::string& value);

	virtual bool isValid() const;

	virtual std::string ToString() const;

protected:

private:
	double mNativeValue;
};


}
}


#endif
