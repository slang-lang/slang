
#ifndef Core_BuildInObjects_UserObject_h
#define Core_BuildInObjects_UserObject_h


// Library includes
#include <string>

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class UserObject : public Object
{
public:
	static std::string DEFAULTVALUE;
	static std::string TYPENAME;

public:
	UserObject(const std::string& name, const std::string& filename, const std::string& type, const std::string& value);
	UserObject(const Object& object);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public: // Operators
	virtual operator bool();

	virtual void operator_assign(Object *other);
	virtual void operator_divide(Object *other);
	virtual bool operator_equal(Object *other);
	virtual bool operator_greater(Object *other);
	virtual bool operator_greater_equal(Object *other);
	virtual bool operator_less(Object *other);
	virtual bool operator_less_equal(Object *other);
	virtual void operator_multiply(Object *other);
	virtual void operator_plus(Object *other);
	virtual void operator_subtract(Object *other);

public: // Value
	virtual std::string ToString() const;
};


}


#endif
