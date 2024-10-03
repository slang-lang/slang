
#ifndef Core_Designtime_BuildInTypes_Int16Type_h
#define Core_Designtime_BuildInTypes_Int16Type_h


// Library includes
#include <inttypes.h>

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Designtime {


class Int16Type : public BluePrintObject
{
public:
	static int16_t DEFAULTVALUE;
	static std::string TYPENAME;

public:
	Int16Type();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

private:
	void initialize();
};


}
}


#endif
