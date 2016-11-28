
// Header
#include "VoidObject.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


std::string VoidObject::TYPENAME = "void";


VoidObject::VoidObject()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	//addInheritance(Ancestor(OBJECT, Ancestor::Type::Extends, Visibility::Public));
}

const std::string& VoidObject::getTypeName() const
{
	return TYPENAME;
}


}
}
