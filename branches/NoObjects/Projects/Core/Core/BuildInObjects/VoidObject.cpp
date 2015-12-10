
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
: Object(object.name(), "SYSTEM.OS", "Void", object.getValue())
{
}

std::string Void::ToString() const
{
	return Typename() + " " + name() + " = " + getValue();
}


}
