
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
	virtual void operator_assign(const BoolObject *other);
	virtual void operator_assign(const Object *other);

	virtual bool operator_bool() const;

	virtual void operator_bitand(const BoolObject *other);
	virtual void operator_bitand(const Object *other);

	virtual void operator_bitor(const BoolObject *other);
	virtual void operator_bitor(const Object *other);

	virtual bool operator_equal(const BoolObject *other);
	virtual bool operator_equal(const Object *other);

	virtual void operator_unary_not();

public: // Value
	virtual bool isValid() const;

	virtual std::string ToString(unsigned int indent) const;

private:

};


}
}


#endif
