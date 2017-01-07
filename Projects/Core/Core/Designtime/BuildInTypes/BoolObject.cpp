
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
	addInheritance(Ancestor(TypeDeclaration(OBJECT), Ancestor::Type::Extends, Visibility::Public));
}

const std::string& BoolObject::getTypeName() const
{
	return TYPENAME;
}


}
}
