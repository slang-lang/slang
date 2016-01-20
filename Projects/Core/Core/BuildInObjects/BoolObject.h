
#ifndef Core_BuildInObjects_Bool_h
#define Core_BuildInObjects_Bool_h


// Library includes

// Project includes
#include <Core/BluePrint.h>
#include <Core/Consts.h>
#include <Core/Object.h>
#include <Core/Symbol.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class BoolObject : public Object
{
public:
	static bool DEFAULTVALUE;
	static std::string TYPENAME;

public:
	BoolObject(bool value = false);
	BoolObject(const std::string& name, bool value);
	BoolObject(const std::string& name, const std::string& value);
	BoolObject(const BoolObject& object);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public:	// Operators
	virtual operator bool() const;

	virtual void operator_assign(BoolObject *other);
	virtual void operator_assign(Object *other);

	virtual void operator_bitand(BoolObject *other);
	virtual void operator_bitand(Object *other);

	virtual void operator_bitor(BoolObject *other);
	virtual void operator_bitor(Object *other);

	virtual bool operator_equal(BoolObject *other);
	virtual bool operator_equal(Object *other);

public: // Value
	virtual bool getNativeValue() const;
	virtual void setNativeValue(bool value);

	virtual std::string getValue() const;
	virtual void setValue(const std::string& value);

	virtual bool isValid() const;

	virtual std::string ToString() const;

private:
	bool mValue;
};


}
}


#endif
