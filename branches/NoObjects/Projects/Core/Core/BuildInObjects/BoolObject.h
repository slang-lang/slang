
#ifndef Core_BuildInObjects_Bool_h
#define Core_BuildInObjects_Bool_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Bool : public Object
{
public:
	Bool(bool value);
	Bool(const std::string& value = "false");
	Bool(const Object& object);

public:	// Operators
	virtual operator bool() const;

	virtual void operator_assign(Object *other);
	virtual bool operator_equal(Object *other);

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
