
#ifndef Core_Runtime_BuildInObjects_UserObject_h
#define Core_Runtime_BuildInObjects_UserObject_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class UserObject : public Object
{
public:
	static std::string DEFAULTVALUE;
	static std::string TYPENAME;

public:
	UserObject();
	UserObject(const std::string& name, const std::string& filename, const std::string& type);
	UserObject(const Object& object);

public: // Operators
	virtual void operator_assign(const Object *other);
	virtual bool operator_bool() const;
	virtual void operator_divide(const Object *other);
	virtual bool operator_equal(const Object *other);
	virtual bool operator_greater(const Object *other);
	virtual bool operator_greater_equal(const Object *other);
	virtual bool operator_less(const Object *other);
	virtual bool operator_less_equal(const Object *other);
	virtual void operator_multiply(const Object *other);
	virtual void operator_plus(const Object *other);
	virtual void operator_subtract(const Object *other);
};


}
}


#endif
