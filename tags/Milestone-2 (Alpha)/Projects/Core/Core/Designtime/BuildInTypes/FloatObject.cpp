
// Header
#include "FloatObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


float FloatObject::DEFAULTVALUE = 0.f;
std::string FloatObject::TYPENAME = "float";


FloatObject::FloatObject()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
}

const std::string& FloatObject::getTypeName() const
{
	return TYPENAME;
}


}
}