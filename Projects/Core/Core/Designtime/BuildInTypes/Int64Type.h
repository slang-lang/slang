
#ifndef Core_Designtime_BuildInTypes_Int64Type_h
#define Core_Designtime_BuildInTypes_Int64Type_h


// Library includes
#include <inttypes.h>

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Designtime {


class Int64Type : public BluePrintObject
{
public:
	static int64_t DEFAULTVALUE;
	static std::string TYPENAME;

public:
	Int64Type();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

private:
	void initialize();
};


}
}


#endif
