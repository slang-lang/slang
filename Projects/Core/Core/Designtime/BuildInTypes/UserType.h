
#ifndef Core_Designtime_BuildInTypes_UserType_h
#define Core_Designtime_BuildInTypes_UserType_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Designtime {


class UserType : public BluePrintObject
{
public:
	static std::string DEFAULTVALUE;
	static std::string TYPENAME;

public:
	UserType();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

private:
	void initialize();
};


}
}


#endif
