
// Header
#include "GenericObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


std::string GenericObject::DEFAULTVALUE = VALUE_NULL;
std::string GenericObject::TYPENAME = OBJECT;


GenericObject::GenericObject()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	// this prevents the user to create an instance of 'Object'
	setImplementationType(ImplementationType::Abstract);
}

const std::string& GenericObject::getTypeName() const
{
	return TYPENAME;
}


}
}
