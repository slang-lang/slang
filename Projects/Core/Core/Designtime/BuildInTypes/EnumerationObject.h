
#ifndef Core_Designtime_BuildInTypes_EnumerationObject_h
#define Core_Designtime_BuildInTypes_EnumerationObject_h


// Library includes

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Designtime {


class EnumerationObject : public BluePrintObject
{
public:
	static int DEFAULTVALUE;
	static std::string TYPENAME;

public:
	EnumerationObject();

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

private:
	void initialize();
};


}
}


#endif
