
// Header
#include "VoidObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


std::string VoidObject::TYPENAME = "void";


VoidObject::VoidObject()
: BluePrint(TYPENAME, SYSTEM_LIBRARY)
{
}

const std::string& VoidObject::getTypeName() const
{
	return TYPENAME;
}


}
}
