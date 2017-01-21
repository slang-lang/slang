
#ifndef Core_Runtime_BuildInObjects_IntegerObject_h
#define Core_Runtime_BuildInObjects_IntegerObject_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class IntegerObject : public Object
{
public:
	static AtomicValue DEFAULTVALUE;
	static std::string TYPENAME;

public:
	IntegerObject(AtomicValue value = DEFAULTVALUE);
	IntegerObject(const std::string& name, int value);
	IntegerObject(const Object& object);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public:	// Operators
	void operator_assign(const IntegerObject *other);
	void operator_assign(const Object *other);

	bool operator_bool() const;

	void operator_divide(const IntegerObject *other);
	void operator_divide(const Object *other);

	bool operator_equal(const IntegerObject *other);
	bool operator_equal(const Object *other);

	bool operator_greater(const IntegerObject *other);
	bool operator_greater(const Object *other);

	bool operator_greater_equal(const IntegerObject *other);
	bool operator_greater_equal(const Object *other);

	bool operator_less(const IntegerObject *other);
	bool operator_less(const Object *other);

	bool operator_less_equal(const IntegerObject *other);
	bool operator_less_equal(const Object *other);

	void operator_modulo(const IntegerObject *other);
	void operator_modulo(const Object *other);

	void operator_multiply(const IntegerObject *other);
	void operator_multiply(const Object *other);

	void operator_plus(const IntegerObject *other);
	void operator_plus(const Object *other);

	void operator_subtract(const IntegerObject *other);
	void operator_subtract(const Object *other);

	void operator_unary_decrement();
	void operator_unary_increment();
	void operator_unary_minus();
	void operator_unary_not();

public: // Values
	bool isValid() const;
};


}
}


#endif
