
#ifndef Core_BuildInObjects_String_h
#define Core_BuildInObjects_String_h


// Library includes
#include <string>

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class String : public Object
{
public:
	static std::string TYPENAME;

public:
	String(const std::string& value = "");
	String(const Object& object);

public:	// Operators
	virtual operator bool() const;

	virtual void operator_assign(BoolObject *other);
	virtual void operator_assign(Number *other);
	virtual void operator_assign(Object *other);
	virtual void operator_assign(String *other);

	virtual bool operator_equal(Object *other);
	virtual bool operator_equal(String *other);

	virtual void operator_plus(BoolObject *other);
	virtual void operator_plus(Number *other);
	virtual void operator_plus(Object *other);
	virtual void operator_plus(String *other);

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
