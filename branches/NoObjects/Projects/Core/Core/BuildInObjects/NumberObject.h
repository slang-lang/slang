
#ifndef Core_BuildInObjects_Number_h
#define Core_BuildInObjects_Number_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Number : public Object
{
public:
	Number(float value = 0.f);
	Number(const std::string& value);
	Number(const Object& object);

public:	// Operators
	virtual operator bool() const;

	virtual void operator_assign(Number *other);
	virtual void operator_assign(Object *other);

	virtual void operator_divide(Number *other);
	virtual void operator_divide(Object *other);

	virtual bool operator_equal(Number *other);
	virtual bool operator_equal(Object *other);

	virtual bool operator_greater(Number *other);
	virtual bool operator_greater(Object *other);

	virtual bool operator_greater_equal(Number *other);
	virtual bool operator_greater_equal(Object *other);

	virtual bool operator_less(Number *other);
	virtual bool operator_less(Object *other);

	virtual bool operator_less_equal(Number *other);
	virtual bool operator_less_equal(Object *other);

	virtual void operator_multiply(Number *other);
	virtual void operator_multiply(Object *other);

	virtual void operator_plus(Number *other);
	virtual void operator_plus(Object *other);

	virtual void operator_subtract(Number *other);
	virtual void operator_subtract(Object *other);

public: // Values
	virtual float getNativeValue() const;
	virtual void setNativeValue(float value);

	virtual std::string getValue() const;
	virtual void setValue(const std::string& value);

	virtual bool isValid() const;

	virtual std::string ToString() const;

protected:

private:
	float mValue;
};


}


#endif
