
#ifndef Core_BuildInObjects_FloatObject_h
#define Core_BuildInObjects_FloatObject_h


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
	static float DEFAULTVALUE;
	static std::string TYPENAME;

public:
	FloatObject(float value = 0.f);
	FloatObject(const std::string& name, float value);
	FloatObject(const std::string& name, const std::string& value);
	FloatObject(const FloatObject& object);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public:	// Operators
	virtual operator bool() const;

	virtual void operator_assign(FloatObject *other);
	virtual void operator_assign(Object *other);

	virtual void operator_divide(FloatObject *other);
	virtual void operator_divide(Object *other);

	virtual bool operator_equal(FloatObject *other);
	virtual bool operator_equal(Object *other);

	virtual bool operator_greater(FloatObject *other);
	virtual bool operator_greater(Object *other);

	virtual bool operator_greater_equal(FloatObject *other);
	virtual bool operator_greater_equal(Object *other);

	virtual bool operator_less(FloatObject *other);
	virtual bool operator_less(Object *other);

	virtual bool operator_less_equal(FloatObject *other);
	virtual bool operator_less_equal(Object *other);

	virtual void operator_multiply(FloatObject *other);
	virtual void operator_multiply(Object *other);

	virtual void operator_plus(FloatObject *other);
	virtual void operator_plus(Object *other);

	virtual void operator_subtract(FloatObject *other);
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
}


#endif
