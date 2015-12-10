
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
	Bool(bool value);
	Bool(const std::string& value = "false");
	Bool(const Object& object);

public:	// Operators
	virtual void operator_assign(Object *other);
	virtual bool operator_equal(Object *other);

	virtual std::string getValue() const;
	virtual bool isValid() const;

	virtual std::string ToString() const;

protected:

private:
	bool mValue;
};


}


#endif
