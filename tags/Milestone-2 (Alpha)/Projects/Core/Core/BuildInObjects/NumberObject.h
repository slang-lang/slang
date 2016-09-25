
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
	NumberObject(AtomicValue value = 0.0);
	NumberObject(const std::string& name, double value);
	NumberObject(const Object& object);

public:	// Operators
	virtual void operator_assign(const NumberObject *other);
	virtual void operator_assign(const Object *other);

	virtual bool operator_bool() const;

	virtual void operator_divide(const NumberObject *other);
	virtual void operator_divide(const Object *other);

	virtual bool operator_equal(const NumberObject *other);
	virtual bool operator_equal(const Object *other);

	virtual bool operator_greater(const NumberObject *other);
	virtual bool operator_greater(const Object *other);

	virtual bool operator_greater_equal(const NumberObject *other);
	virtual bool operator_greater_equal(const Object *other);

	virtual bool operator_less(const NumberObject *other);
	virtual bool operator_less(const Object *other);

	virtual bool operator_less_equal(const NumberObject *other);
	virtual bool operator_less_equal(const Object *other);

	virtual void operator_multiply(const NumberObject *other);
	virtual void operator_multiply(const Object *other);

	virtual void operator_plus(const NumberObject *other);
	virtual void operator_plus(const Object *other);

	virtual void operator_subtract(const NumberObject *other);
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
