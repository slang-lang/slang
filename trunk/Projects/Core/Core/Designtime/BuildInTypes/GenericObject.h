
#ifndef Core_Designtime_BuildInTypes_GenericObject_h
#define Core_Designtime_BuildInTypes_GenericObject_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class GenericObject : public BluePrintObject
{
public:
	static std::string DEFAULTVALUE;
	static std::string TYPENAME;

public:
	GenericObject();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;
};


}
}


#endif
