
#ifndef Core_Designtime_BuildInTypes_NumberObject_h
#define Core_Designtime_BuildInTypes_NumberObject_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class NumberObject : public BluePrintObject
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
