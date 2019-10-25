
#ifndef Core_Runtime_BuildInTypes_BoolObject_h
#define Core_Runtime_BuildInTypes_BoolObject_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class BoolObject : public Object
{
public:
	static AtomicValue DEFAULTVALUE;
	static std::string TYPENAME;

public:
	explicit BoolObject(const AtomicValue& value = DEFAULTVALUE);
	explicit BoolObject(const std::string& name, const AtomicValue& value);
	explicit BoolObject(const Object& other);

public:	// Operators
	void operator_assign(const Object *other);
	bool operator_bool() const;
	bool operator_equal(const Object *other);
	void operator_unary_not();
};


}
}


#endif
