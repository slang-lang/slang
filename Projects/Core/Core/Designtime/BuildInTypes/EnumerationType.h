
#ifndef Core_Designtime_BuildInTypes_EnumerationType_h
#define Core_Designtime_BuildInTypes_EnumerationType_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Designtime {


class EnumerationType : public BluePrintObject
{
public:
	static int32_t DEFAULTVALUE;
	static std::string TYPENAME;

public:
	EnumerationType();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

private:
	void initialize();
};


}
}


#endif
