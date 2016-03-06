
// Header
#include "GenericObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


std::string GenericObject::DEFAULTVALUE = VALUE_NULL;
std::string GenericObject::TYPENAME = GENERIC_OBJECT;


GenericObject::GenericObject()
: BluePrint(TYPENAME, SYSTEM_LIBRARY)
{
}

const std::string& GenericObject::getTypeName() const
{
	return TYPENAME;
}


}
}
