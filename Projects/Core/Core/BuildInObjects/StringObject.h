
#ifndef Core_Runtime_BuildInObjects_String_h
#define Core_Runtime_BuildInObjects_String_h


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
	static AtomicValue DEFAULTVALUE;
	static std::string TYPENAME;

public:
	explicit StringObject(const AtomicValue& value = DEFAULTVALUE);
	explicit StringObject(const std::string& value);
	explicit StringObject(const std::string& name, const AtomicValue& value);
	explicit StringObject(const Object& other);

public:	// Operators
	void operator_assign(const Object* other);
	void operator_assign(const StringObject* other);

	bool operator_bool() const;

	bool operator_equal(const Object* other);
	bool operator_equal(const StringObject* other);

	bool operator_greater(const StringObject *other);
	bool operator_greater(const Object *other);

	bool operator_greater_equal(const StringObject *other);
	bool operator_greater_equal(const Object *other);

	bool operator_less(const StringObject *other);
	bool operator_less(const Object *other);

	bool operator_less_equal(const StringObject *other);
	bool operator_less_equal(const Object *other);

	void operator_plus(const Object* other);
	void operator_plus(const StringObject* other);

public: // Value
	bool isValid() const;
};


}
}


#endif
