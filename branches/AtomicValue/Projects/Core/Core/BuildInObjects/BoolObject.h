
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
	static bool DEFAULTVALUE;
	static AtomicValue ATOMIC_DEFAULTVALUE;
	static std::string TYPENAME;

public:
	BoolObject(AtomicValue value = DEFAULTVALUE);
	BoolObject(const std::string& name, bool value);
	BoolObject(const Object& other);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public:	// Operators
	virtual void operator_assign(BoolObject *other);
	virtual void operator_assign(Object *other);

	virtual bool operator_bool() const;

	virtual void operator_bitand(BoolObject *other);
	virtual void operator_bitand(Object *other);

	virtual void operator_bitor(BoolObject *other);
	virtual void operator_bitor(Object *other);

	virtual bool operator_equal(BoolObject *other) const;
	virtual bool operator_equal(Object *other) const;

	virtual void operator_unary_not();

public: // Value
	virtual bool isValid() const;

	virtual std::string ToString() const;

private:

};


}
}


#endif
