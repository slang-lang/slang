
// Header
#include "VoidObject.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Consts.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


std::string VoidObject::TYPENAME = "void";


VoidObject::VoidObject()
: Object("<unnamed object>", SYSTEM_LIBRARY, TYPENAME, "<VOID>")
{
	mIsAtomicType = true;

	Constructor(ParameterList());
}

VoidObject::VoidObject(const Object& object)
: Object(object.getName(), SYSTEM_LIBRARY, TYPENAME, object.getValue())
{
}

VoidObject::operator bool() const
{
	return false;
}

void VoidObject::getNativeValue() const
{
	return;	// this makes absolutely no sense but hey :-)
}

std::string VoidObject::getValue() const
{
	return "<VOID>";
}

void VoidObject::setNativeValue(void)
{
}

void VoidObject::setValue(const std::string&)
{
}

std::string VoidObject::ToString() const
{
	return Typename() + " " + getName() + " = " + getValue();
}


}
