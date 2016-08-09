
#ifndef Core_Designtime_BuildInTypes_FloatObject_h
#define Core_Designtime_BuildInTypes_FloatObject_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class FloatObject : public BluePrintObject
{
public:
	static float DEFAULTVALUE;
	static std::string TYPENAME;

public:
	FloatObject();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;
};


}
}


#endif
