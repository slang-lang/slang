
// Header
#include "DoubleObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


double DoubleObject::DEFAULTVALUE = 0.0;
std::string DoubleObject::TYPENAME = "double";


DoubleObject::DoubleObject()
: BluePrint(TYPENAME, SYSTEM_LIBRARY)
{
}

const std::string& DoubleObject::getTypeName() const
{
	return TYPENAME;
}


}
}
