
// Header
#include "BoolObject.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


bool BoolObject::DEFAULTVALUE = false;
std::string BoolObject::TYPENAME = "bool";


BoolObject::BoolObject()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	addInheritance(Ancestor(OBJECT, Ancestor::Type::Extends, Visibility::Public, PrototypeConstraints()));
}

const std::string& BoolObject::getTypeName() const
{
	return TYPENAME;
}


}
}
