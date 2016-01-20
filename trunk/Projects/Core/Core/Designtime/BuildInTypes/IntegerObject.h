
#ifndef Core_Designtime_BuildInTypes_IntegerObject_h
#define Core_Designtime_BuildInTypes_IntegerObject_h


// Library includes

// Project includes
#include <Core/BluePrint.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class IntegerObject : public BluePrint
{
public:
	static int DEFAULTVALUE;
	static std::string TYPENAME;

public:
	IntegerObject();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;
};


}
}


#endif
