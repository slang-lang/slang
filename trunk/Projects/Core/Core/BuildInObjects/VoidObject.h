
#ifndef Core_Runtime_BuildInObjects_VoidObject_h
#define Core_Runtime_BuildInObjects_VoidObject_h


// Library includes
#include <string>

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class VoidObject : public Object
{
public:
	static std::string TYPENAME;

public:
	VoidObject();
	VoidObject(const std::string& name);
	VoidObject(const Object& other);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public:	// Operators
	virtual operator bool() const;

public: // Value
	virtual void getNativeValue() const;
	virtual void setNativeValue(void);

	virtual std::string getValue() const;
	virtual void setValue(const std::string& value);

	virtual std::string ToString() const;
};


}
}


#endif
