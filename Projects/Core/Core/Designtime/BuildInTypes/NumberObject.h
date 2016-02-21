
#ifndef Core_Designtime_BuildInTypes_NumberObject_h
#define Core_Designtime_BuildInTypes_NumberObject_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrint.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class NumberObject : public BluePrint
{
public:
	static double DEFAULTVALUE;
	static std::string TYPENAME;

public:
	NumberObject();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;
};


}
}


#endif
