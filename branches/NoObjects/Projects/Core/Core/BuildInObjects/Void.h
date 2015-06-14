
#ifndef Core_BuildInObjects_Void_h
#define Core_BuildInObjects_Void_h


// Library includes
#include <string>

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Void : public Object
{
public:
	Void();

public:
	virtual void operator_assign(Object *other);
	virtual void operator_divide(Object *other);
	virtual void operator_multiply(Object *other);
	virtual void operator_plus(Object *other);
	virtual void operator_subtract(Object *other);

	virtual std::string ToString() const;
};


}


#endif
