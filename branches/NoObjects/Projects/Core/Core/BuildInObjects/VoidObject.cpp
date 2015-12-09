
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

void Void::operator_assign(Object * /*other*/)
{
	throw Utils::NotImplemented("operator=");
}

void Void::operator_divide(Object * /*other*/)
{
	throw Utils::NotImplemented("operator/");
}

void Void::operator_multiply(Object * /*other*/)
{
	throw Utils::NotImplemented("operator*");
}

void Void::operator_plus(Object * /*other*/)
{
	throw Utils::NotImplemented("operator+");
}

void Void::operator_subtract(Object * /*other*/)
{
	throw Utils::NotImplemented("operator-");
}

std::string Void::ToString() const
{
	return "";
}


}
