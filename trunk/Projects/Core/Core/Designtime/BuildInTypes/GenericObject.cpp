
// Header
#include "GenericObject.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Consts.h>


// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


std::string GenericObject::DEFAULTVALUE = VALUE_NULL;
std::string GenericObject::TYPENAME = _object;


GenericObject::GenericObject()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	// this prevents the user to create an instance of 'Object'
	setImplementationType(ImplementationType::Abstract);

	initialize();
}

const std::string& GenericObject::getTypeName() const
{
	return TYPENAME;
}

void GenericObject::initialize()
{
	// nothing to do here atm
}


}
}
