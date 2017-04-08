
#ifndef Core_Designtime_BuildInTypes_UserObject_h
#define Core_Designtime_BuildInTypes_UserObject_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class UserObject : public BluePrintObject
{
public:
	static std::string DEFAULTVALUE;
	static std::string TYPENAME;

public:
	UserObject();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

private:
	void initialize();
};


}
}


#endif
