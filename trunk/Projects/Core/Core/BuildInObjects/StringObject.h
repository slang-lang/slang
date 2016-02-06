
#ifndef Core_BuildInObjects_String_h
#define Core_BuildInObjects_String_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class StringObject : public Object
{
public:
	static std::string DEFAULTVALUE;
	static std::string TYPENAME;

public:
	StringObject(const std::string& value = "");
	StringObject(const std::string& name, const std::string& value);
	StringObject(const Object& other);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public:	// Operators
	virtual operator bool() const;

	virtual void operator_assign(Object *other);
	virtual void operator_assign(StringObject *other);

	virtual bool operator_equal(Object *other);
	virtual bool operator_equal(StringObject *other);

	virtual void operator_plus(Object *other);
	virtual void operator_plus(StringObject *other);

public: // Value
	virtual std::string getNativeValue() const;
	virtual void setNativeValue(const std::string& value);

	virtual std::string getValue() const;
	virtual void setValue(const std::string& value);

	virtual bool isValid() const;

	virtual std::string ToString() const;

private:
	std::string mNativeValue;
};


}
}


#endif
