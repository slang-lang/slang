
#ifndef Core_Designtime_BuildInTypes_DoubleObject_h
#define Core_Designtime_BuildInTypes_DoubleObject_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrint.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class DoubleObject : public BluePrint
{
public:
	static double DEFAULTVALUE;
	static std::string TYPENAME;

public:
	DoubleObject();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;
};


}
}


#endif
