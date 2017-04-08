
#ifndef Core_Designtime_BuildInTypes_IntegerObject_h
#define Core_Designtime_BuildInTypes_IntegerObject_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class IntegerObject : public BluePrintObject
{
public:
	static int DEFAULTVALUE;
	static std::string TYPENAME;

public:
	IntegerObject();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

private:
	void initialize();
};


}
}


#endif
