
// Header
#include "VoidObject.h"

// Library includes

// Project includes
#include <Core/Tools.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


std::string VoidObject::TYPENAME = "void";


VoidObject::VoidObject()
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue())
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

VoidObject::VoidObject(const std::string& name)
: Object(name, SYSTEM_LIBRARY, TYPENAME, AtomicValue())
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

VoidObject::VoidObject(const Object& object)
: Object(object.getName(), SYSTEM_LIBRARY, TYPENAME, AtomicValue())
{
	mIsAtomicType = true;
	mIsConstructed = true;
}

bool VoidObject::isValid() const
{
	return false;
}

bool VoidObject::operator_bool() const
{
	return mIsConstructed;
}


}
}
