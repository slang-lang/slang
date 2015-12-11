
// Header
#include "VoidObject.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


Void::Void()
: Object("", "SYSTEM.OS", "Void", "")
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

Void::Void(const Object& object)
: Object(object.getName(), "SYSTEM.OS", "Void", object.getValue())
{
}

Void::operator bool() const
{
	return false;
}

std::string Void::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
