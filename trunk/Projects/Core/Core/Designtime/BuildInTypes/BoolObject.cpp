
// Header
#include "BoolObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


bool BoolObject::DEFAULTVALUE = false;
std::string BoolObject::TYPENAME = "bool";


BoolObject::BoolObject()
: BluePrint(TYPENAME, SYSTEM_LIBRARY)
{
}

const std::string& BoolObject::getTypeName() const
{
	return TYPENAME;
}


}
}
