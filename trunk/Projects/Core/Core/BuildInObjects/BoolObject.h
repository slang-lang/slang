
#ifndef Core_Runtime_BuildInObjects_BoolObject_h
#define Core_Runtime_BuildInObjects_BoolObject_h


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
	BoolObject(AtomicValue value = DEFAULTVALUE);
	BoolObject(const std::string& name, bool value);
	BoolObject(const Object& other);

public:	// Operators
	void operator_assign(const BoolObject *other);
	void operator_assign(const Object *other);

	bool operator_bool() const;

	void operator_bitand(const BoolObject *other);
	void operator_bitand(const Object *other);

	void operator_bitor(const BoolObject *other);
	void operator_bitor(const Object *other);

	bool operator_equal(const BoolObject *other);
	bool operator_equal(const Object *other);

	void operator_unary_not();

public: // Value
	bool isValid() const;
};


}
}


#endif