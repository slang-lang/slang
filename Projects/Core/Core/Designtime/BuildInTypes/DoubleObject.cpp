
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
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	mIsAtomicType = true;

	addInheritance(Ancestor(TypeDeclaration(OBJECT), Ancestor::Type::Extends, Visibility::Public));
}

const std::string& DoubleObject::getTypeName() const
{
	return TYPENAME;
}


}
}
