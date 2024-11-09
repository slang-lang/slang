
#ifndef Core_Designtime_BuildInTypes_Int32Type_h
#define Core_Designtime_BuildInTypes_Int32Type_h


// Library includes
#include <inttypes.h>

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Designtime {


class Int32Type : public BluePrintObject
{
public:
	static int32_t DEFAULTVALUE;
	static std::string TYPENAME;

public:
	Int32Type();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

private:
	void initialize();
};


}
}


#endif
