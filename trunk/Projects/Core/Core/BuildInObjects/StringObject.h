
#ifndef Core_BuildInObjects_String_h
#define Core_BuildInObjects_String_h


// Library includes
#include <string>

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class StringObject : public Object
{
public:
	static std::string TYPENAME;

public:
	StringObject(const std::string& value = "");
	StringObject(const Object& object);

public:	// Operators
	virtual operator bool() const;

	virtual void operator_assign(BoolObject *other);
	virtual void operator_assign(FloatObject *other);
	virtual void operator_assign(IntegerObject *other);
	virtual void operator_assign(NumberObject *other);
	virtual void operator_assign(Object *other);
	virtual void operator_assign(StringObject *other);

	virtual bool operator_equal(Object *other);
	virtual bool operator_equal(StringObject *other);

	virtual void operator_plus(BoolObject *other);
	virtual void operator_plus(FloatObject *other);
	virtual void operator_plus(IntegerObject *other);
	virtual void operator_plus(NumberObject *other);
	virtual void operator_plus(Object *other);
	virtual void operator_plus(StringObject *other);

public: // Value
	virtual std::string getNativeValue() const;
	virtual void setNativeValue(const std::string& value);

	virtual std::string getValue() const;
	virtual void setValue(const std::string& value);

	virtual std::string ToString() const;

private:
	std::string mValue;
};


}


#endif
