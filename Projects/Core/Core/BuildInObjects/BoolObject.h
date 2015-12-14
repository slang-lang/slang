
#ifndef Core_BuildInObjects_Bool_h
#define Core_BuildInObjects_Bool_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class BoolObject : public Object
{
public:
	static std::string TYPENAME;

public:
	BoolObject(bool value = false);
	BoolObject(const std::string& value);
	BoolObject(const Object& object);

public:	// Operators
	virtual operator bool() const;

	virtual void operator_assign(BoolObject *other);
	virtual void operator_assign(NumberObject *other);
	virtual void operator_assign(Object *other);
	virtual void operator_assign(StringObject *other);

	virtual bool operator_equal(BoolObject *other);
	virtual bool operator_equal(NumberObject *other);
	virtual bool operator_equal(Object *other);
	virtual bool operator_equal(StringObject *other);

public: // Value
	virtual bool getNativeValue() const;
	virtual void setNativeValue(bool value);

	virtual std::string getValue() const;
	virtual void setValue(const std::string& value);

	virtual bool isValid() const;

	virtual std::string ToString() const;

private:
	bool mValue;
};


}


#endif
