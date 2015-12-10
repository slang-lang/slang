
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
	String(const Object& object);

public:	// Operators
	virtual void operator_assign(Object *other);
	virtual bool operator_equal(Object *other);
	virtual void operator_plus(Object *other);

	virtual std::string ToString() const;
};


}


#endif
