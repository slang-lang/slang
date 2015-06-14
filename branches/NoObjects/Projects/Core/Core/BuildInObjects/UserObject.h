
#ifndef Core_BuildInObjects_UserObject_h
#define Core_BuildInObjects_UserObject_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class UserObject : public Object
{
public:
	UserObject(const std::string& name, const std::string& filename, const std::string& type, const std::string& value)
	: Object(name, filename, type, value)
	{
	}

public:

protected:

private:

};


}


#endif
