
// Header
#include "StringObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


std::string StringObject::DEFAULTVALUE = "";
std::string StringObject::TYPENAME = "string";


StringObject::StringObject()
: BluePrint(TYPENAME, SYSTEM_LIBRARY)
{
}

const std::string& StringObject::getTypeName() const
{
	return TYPENAME;
}


}
}
