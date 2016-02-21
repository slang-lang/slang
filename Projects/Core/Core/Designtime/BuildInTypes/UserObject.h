
#ifndef Core_Designtime_BuildInTypes_UserObject_h
#define Core_Designtime_BuildInTypes_UserObject_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrint.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class UserObject : public BluePrint
{
public:
	static std::string DEFAULTVALUE;
	static std::string TYPENAME;

public:
	UserObject();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;
};


}
}


#endif
