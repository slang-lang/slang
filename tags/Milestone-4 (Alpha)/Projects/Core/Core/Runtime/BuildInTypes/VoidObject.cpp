
// Header
#include "VoidObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


std::string VoidObject::TYPENAME = _void;


VoidObject::VoidObject()
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue())
{
	mIsAtomicType = true;
}

VoidObject::VoidObject(const std::string& name)
: Object(name, SYSTEM_LIBRARY, TYPENAME, AtomicValue())
{
	mIsAtomicType = true;
}

VoidObject::VoidObject(const Object& object)
: Object(object.getName(), SYSTEM_LIBRARY, TYPENAME, AtomicValue())
{
	mIsAtomicType = true;
}

bool VoidObject::isValid() const
{
	return false;
}

bool VoidObject::operator_bool() const
{
	return false;
}


}
}
