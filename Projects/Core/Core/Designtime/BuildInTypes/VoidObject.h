
#ifndef Core_Designtime_BuildInTypes_VoidObject_h
#define Core_Designtime_BuildInTypes_VoidObject_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Designtime {


class VoidObject : public BluePrintObject
{
public:
	static std::string TYPENAME;

public:
	VoidObject();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

private:
	void initialize();
};


}
}


#endif
