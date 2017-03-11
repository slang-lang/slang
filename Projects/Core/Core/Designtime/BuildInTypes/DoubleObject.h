
#ifndef Core_Designtime_BuildInTypes_DoubleObject_h
#define Core_Designtime_BuildInTypes_DoubleObject_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class DoubleObject : public BluePrintObject
{
public:
	static double DEFAULTVALUE;
	static std::string TYPENAME;

public:
	DoubleObject();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

private:
	void initialize();
};


}
}


#endif
