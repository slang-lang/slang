
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
	static AtomicValue DEFAULTVALUE;
	static std::string TYPENAME;

public:
	UserObject();
	UserObject(const std::string& name, const std::string& filename, const std::string& type, bool isNull = false);
	UserObject(const Object& object);

public: // Operators
	void operator_assign(const Object *other);
	bool operator_bool() const;
	void operator_divide(const Object *other);
	bool operator_equal(const Object *other);
	bool operator_greater(const Object *other);
	bool operator_greater_equal(const Object *other);
	bool operator_less(const Object *other);
	bool operator_less_equal(const Object *other);
	void operator_multiply(const Object *other);
	void operator_plus(const Object *other);
	void operator_subtract(const Object *other);
};


}
}


#endif
