
#ifndef Core_Designtime_BuildInTypes_FloatType_h
#define Core_Designtime_BuildInTypes_FloatType_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Designtime {


class FloatType : public BluePrintObject
{
public:
	static float DEFAULTVALUE;
	static std::string TYPENAME;

public:
	FloatType();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

private:
	void initialize();
};


}
}


#endif
