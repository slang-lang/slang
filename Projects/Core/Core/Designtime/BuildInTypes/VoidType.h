
#ifndef Core_Designtime_BuildInTypes_VoidType_h
#define Core_Designtime_BuildInTypes_VoidType_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Designtime {


class VoidType : public BluePrintObject
{
public:
	static std::string TYPENAME;

public:
	VoidType();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

private:
	void initialize();
};


}
}


#endif
