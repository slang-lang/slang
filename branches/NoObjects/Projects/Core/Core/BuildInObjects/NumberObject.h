
#ifndef Core_BuildInObjects_Number_h
#define Core_BuildInObjects_Number_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Number : public Object
{
public:
	Number(const std::string& value = "0");
	Number(const Object& object);

public:	// Operators
	virtual void operator_assign(Object *other);
	virtual void operator_divide(Object *other);
	virtual void operator_multiply(Object *other);
	virtual void operator_plus(Object *other);
	virtual void operator_subtract(Object *other);

	virtual bool isValid() const;

	virtual std::string ToString() const;

protected:

private:

};


}


#endif
