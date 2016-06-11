
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
	static std::string DEFAULTVALUE;
	static std::string TYPENAME;

public:
	StringObject(AtomicValue value = "");
	StringObject(const std::string& name, const std::string& value);
	StringObject(const Object& other);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public:	// Operators
	virtual void operator_assign(const Object *other);
	virtual void operator_assign(const StringObject *other);

	virtual bool operator_bool() const;

	virtual bool operator_equal(const Object *other);
	virtual bool operator_equal(const StringObject *other);

	virtual void operator_plus(const Object *other);
	virtual void operator_plus(const StringObject *other);

public: // Value
	virtual bool isValid() const;

	virtual std::string ToString() const;

private:

};


}
}


#endif
