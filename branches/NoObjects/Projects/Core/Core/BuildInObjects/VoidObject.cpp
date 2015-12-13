
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

void Void::getNativeValue() const
{
	return;	// this makes absolutely no sense but hey :-)
}

std::string Void::getValue() const
{
	return "<VOID>";
}

void Void::setNativeValue(void)
{
}

void Void::setValue(const std::string&)
{
}

std::string Void::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
