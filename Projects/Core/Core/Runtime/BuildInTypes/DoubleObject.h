
#ifndef Core_Runtime_BuildInTypes_DoubleObject_h
#define Core_Runtime_BuildInTypes_DoubleObject_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class DoubleObject : public Object
{
public:
	static AtomicValue DEFAULTVALUE;
	static std::string TYPENAME;

public:
	explicit DoubleObject(const AtomicValue& value = DEFAULTVALUE);
	explicit DoubleObject(const std::string& name, const AtomicValue& value);
	explicit DoubleObject(const Object& object);

public:	// Operators
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
	void operator_unary_decrement();
	void operator_unary_increment();
	void operator_unary_minus();
	void operator_unary_not();
};


}
}


#endif
