
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
}

void Void::operator_assign(Object * /*other*/)
{
	throw Utils::Exception("operator= not implemented");
}

void Void::operator_divide(Object * /*other*/)
{
	throw Utils::Exception("operator/ not implemented");
}

void Void::operator_multiply(Object * /*other*/)
{
	throw Utils::Exception("operator* not implemented");
}

void Void::operator_plus(Object * /*other*/)
{
	throw Utils::Exception("operator+ not implemented");
}

void Void::operator_subtract(Object * /*other*/)
{
	throw Utils::Exception("operator- not implemented");
}

std::string Void::ToString() const
{
	return "";
}

void Void::setValue(void)
{
}


}
