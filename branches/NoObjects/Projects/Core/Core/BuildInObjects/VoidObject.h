
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
	Void(const Object& object);

public:
	virtual std::string ToString() const;
};


}


#endif
