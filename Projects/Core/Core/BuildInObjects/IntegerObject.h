
#ifndef Core_BuildInObjects_IntegerObject_h
#define Core_BuildInObjects_IntegerObject_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class IntegerObject : public Object
{
public:
	static int DEFAULTVALUE;
	static std::string TYPENAME;

public:
	IntegerObject(int value = 0);
	IntegerObject(const std::string& name, int value);
	IntegerObject(const std::string& name, const std::string& value);
	IntegerObject(const Object& object);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public:	// Operators
	virtual operator bool() const;

	virtual void operator_assign(IntegerObject *other);
	virtual void operator_assign(Object *other);

	virtual void operator_divide(IntegerObject *other);
	virtual void operator_divide(Object *other);

	virtual bool operator_equal(IntegerObject *other);
	virtual bool operator_equal(Object *other);

	virtual bool operator_greater(IntegerObject *other);
	virtual bool operator_greater(Object *other);

	virtual bool operator_greater_equal(IntegerObject *other);
	virtual bool operator_greater_equal(Object *other);

	virtual bool operator_less(IntegerObject *other);
	virtual bool operator_less(Object *other);

	virtual bool operator_less_equal(IntegerObject *other);
	virtual bool operator_less_equal(Object *other);

	virtual void operator_modulo(IntegerObject *other);
	virtual void operator_modulo(Object *other);

	virtual void operator_multiply(IntegerObject *other);
	virtual void operator_multiply(Object *other);

	virtual void operator_plus(IntegerObject *other);
	virtual void operator_plus(Object *other);

	virtual void operator_subtract(IntegerObject *other);
	virtual void operator_subtract(Object *other);

public: // Values
	virtual int getNativeValue() const;
	virtual void setNativeValue(int value);

	virtual std::string getValue() const;
	virtual void setValue(const std::string& value);

	virtual bool isValid() const;

	virtual std::string ToString() const;

protected:

private:
	int mValue;
};


}


#endif
