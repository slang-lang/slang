
// Header
#include "IntegerObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


int IntegerObject::DEFAULTVALUE = 0;
std::string IntegerObject::TYPENAME = "int";


IntegerObject::IntegerObject()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	addInheritance(Ancestor(OBJECT, Ancestor::Type::Extends, Visibility::Public));
}

const std::string& IntegerObject::getTypeName() const
{
	return TYPENAME;
}


}
}
