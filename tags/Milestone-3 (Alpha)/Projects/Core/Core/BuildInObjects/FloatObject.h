
#ifndef Core_Runtime_BuildInObjects_FloatObject_h
#define Core_Runtime_BuildInObjects_FloatObject_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class FloatObject : public Object
{
public:
	static AtomicValue DEFAULTVALUE;
	static std::string TYPENAME;

public:
	FloatObject(AtomicValue value = DEFAULTVALUE);
	FloatObject(const std::string& name, float value);
	FloatObject(const Object& object);

public:	// Operators
	virtual void operator_assign(const FloatObject *other);
	virtual void operator_assign(const Object *other);

	virtual bool operator_bool() const;

	virtual void operator_divide(const FloatObject *other);
	virtual void operator_divide(const Object *other);

	virtual bool operator_equal(const FloatObject *other);
	virtual bool operator_equal(const Object *other);

	virtual bool operator_greater(const FloatObject *other);
	virtual bool operator_greater(const Object *other);

	virtual bool operator_greater_equal(const FloatObject *other);
	virtual bool operator_greater_equal(const Object *other);

	virtual bool operator_less(const FloatObject *other);
	virtual bool operator_less(const Object *other);

	virtual bool operator_less_equal(const FloatObject *other);
	virtual bool operator_less_equal(const Object *other);

	virtual void operator_multiply(const FloatObject *other);
	virtual void operator_multiply(const Object *other);

	virtual void operator_plus(const FloatObject *other);
	virtual void operator_plus(const Object *other);

	virtual void operator_subtract(const FloatObject *other);
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
