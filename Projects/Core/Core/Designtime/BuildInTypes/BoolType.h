
#ifndef Core_Designtime_BuildInTypes_BoolType_h
#define Core_Designtime_BuildInTypes_BoolType_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Designtime {


class BoolType : public BluePrintObject
{
public:
	static bool DEFAULTVALUE;
	static std::string TYPENAME;

public:
	BoolType();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

private:
	void initialize();
};


}
}


#endif
