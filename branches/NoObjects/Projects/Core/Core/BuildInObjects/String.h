
#ifndef Core_BuildInObjects_String_h
#define Core_BuildInObjects_String_h


// Library includes
#include <string>

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class String : public Object
{
public:
	String(const std::string& value = "");

public:	// Operators
	virtual void operator_assign(Object *other);
	virtual void operator_divide(Object *other);
	virtual void operator_multiply(Object *other);
	virtual void operator_plus(Object *other);
	virtual void operator_subtract(Object *other);

	virtual std::string ToString() const;
};


}


#endif
