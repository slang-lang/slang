
#ifndef Core_Runtime_BuildInObjects_Number_h
#define Core_Runtime_BuildInObjects_Number_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class NumberObject : public Object
{
public:
	static double DEFAULTVALUE;
	static std::string TYPENAME;

public:
	NumberObject(double value = 0.0);
	NumberObject(AtomicValue value);
	NumberObject(const std::string& name, double value);
	NumberObject(const Object& object);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public:	// Operators
	virtual void operator_assign(NumberObject *other);
	virtual void operator_assign(Object *other);

	virtual bool operator_bool() const;

	virtual void operator_divide(NumberObject *other);
	virtual void operator_divide(Object *other);

	virtual bool operator_equal(NumberObject *other) const;
	virtual bool operator_equal(Object *other) const;

	virtual bool operator_greater(NumberObject *other) const;
	virtual bool operator_greater(Object *other) const;

	virtual bool operator_greater_equal(NumberObject *other) const;
	virtual bool operator_greater_equal(Object *other) const;

	virtual bool operator_less(NumberObject *other) const;
	virtual bool operator_less(Object *other) const;

	virtual bool operator_less_equal(NumberObject *other) const;
	virtual bool operator_less_equal(Object *other) const;

	virtual void operator_multiply(NumberObject *other);
	virtual void operator_multiply(Object *other);

	virtual void operator_plus(NumberObject *other);
	virtual void operator_plus(Object *other);

	virtual void operator_subtract(NumberObject *other);
	virtual void operator_subtract(Object *other);

	virtual void operator_unary_decrement();
	virtual void operator_unary_increment();
	virtual void operator_unary_minus();
	virtual void operator_unary_not();

public: // Values
	virtual double getNativeValue() const;
	virtual void setNativeValue(double value);

	virtual bool isValid() const;

	virtual std::string ToString() const;

protected:

private:
	double mNativeValue;
};


}
}


#endif
