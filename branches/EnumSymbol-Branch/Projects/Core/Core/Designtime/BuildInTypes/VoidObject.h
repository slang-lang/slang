
#ifndef Core_Designtime_BuildInTypes_VoidObject_h
#define Core_Designtime_BuildInTypes_VoidObject_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrint.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class VoidObject : public BluePrint
{
public:
	static std::string TYPENAME;

public:
	VoidObject();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;
};


}
}


#endif
