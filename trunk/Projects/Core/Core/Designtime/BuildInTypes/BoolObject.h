
#ifndef Core_Designtime_BuildInTypes_BoolObject_h
#define Core_Designtime_BuildInTypes_BoolObject_h


// Library includes

// Project includes
#include <Core/BluePrint.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class BoolObject : public BluePrint
{
public:
	static bool DEFAULTVALUE;
	static std::string TYPENAME;

public:
	BoolObject();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;
};


}
}


#endif
