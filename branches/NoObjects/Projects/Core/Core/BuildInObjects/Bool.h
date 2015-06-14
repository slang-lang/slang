
#ifndef Core_BuildInObjects_Bool_h
#define Core_BuildInObjects_Bool_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Bool : public Object
{
public:
	Bool(const std::string& value = "false");

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
