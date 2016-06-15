
// Header
#include "NumberObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


double NumberObject::DEFAULTVALUE = 0.0;
std::string NumberObject::TYPENAME = "number";


NumberObject::NumberObject()
: BluePrint(TYPENAME, SYSTEM_LIBRARY)
{
}

const std::string& NumberObject::getTypeName() const
{
	return TYPENAME;
}


}
}
