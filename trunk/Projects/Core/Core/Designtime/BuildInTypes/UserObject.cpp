
// Header
#include "UserObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


std::string UserObject::DEFAULTVALUE = VALUE_NONE;
std::string UserObject::TYPENAME = OBJECT;


UserObject::UserObject()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
}

const std::string& UserObject::getTypeName() const
{
	return TYPENAME;
}


}
}
