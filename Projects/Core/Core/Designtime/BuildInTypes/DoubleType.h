
#ifndef Core_Designtime_BuildInTypes_DoubleType_h
#define Core_Designtime_BuildInTypes_DoubleType_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Designtime {


class DoubleType : public BluePrintObject
{
public:
	static double DEFAULTVALUE;
	static std::string TYPENAME;

public:
	DoubleType();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

private:
	void initialize();
};


}
}


#endif
