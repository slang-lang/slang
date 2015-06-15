
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
	UserObject(const std::string& name, const std::string& filename, const std::string& type, const std::string& value);

public:	// Operators
	virtual void operator_assign(Object *other);
	virtual void operator_divide(Object *other);
	virtual void operator_multiply(Object *other);
	virtual void operator_plus(Object *other);
	virtual void operator_subtract(Object *other);

	virtual std::string ToString() const;

	virtual void setValue(UserObject *val);
};


}


#endif
