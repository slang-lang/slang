
// Header
#include "Math.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/NumberObject.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Math {


Object add(Object& v1, Object& v2)
{
	Object result;

	if ( v1.Typename() == NumberObject::TYPENAME && v2.Typename() == NumberObject::TYPENAME ) {
		// none of our summands is a string
		float f1 = Tools::stringToFloat(v1.getValue());
		float f2 = Tools::stringToFloat(v2.getValue());

		result = NumberObject(Tools::toString(f1 + f2));
	}
	else {
		throw Utils::Exceptions::TypeMismatch("for addition: '" + v1.getValue() + "' and/or '" + v2.getValue() + "' are not of type 'NumberObject'");
	}

	return result;
}

Object divide(Object& v1, Object& v2)
{
	Object result;

	if ( v1.Typename() == NumberObject::TYPENAME && v2.Typename() == NumberObject::TYPENAME ) {
		// none of our summands is a string
		float f1 = Tools::stringToFloat(v1.getValue());
		float f2 = Tools::stringToFloat(v2.getValue());

		result = NumberObject(Tools::toString(f1 / f2));
	}
	else {
		throw Utils::Exceptions::TypeMismatch("for division: '" + v1.getValue() + "' and/or '" + v2.getValue() + "' are not of type 'NumberObject'");
	}

	return result;
}

Object multiply(Object& v1, Object& v2)
{
	Object result;

	if ( v1.Typename() == NumberObject::TYPENAME && v2.Typename() == NumberObject::TYPENAME ) {
		// none of our summands is a string
		float f1 = Tools::stringToFloat(v1.getValue());
		float f2 = Tools::stringToFloat(v2.getValue());

		result = NumberObject(Tools::toString(f1 * f2));
	}
	else {
		throw Utils::Exceptions::TypeMismatch("for multiplication: '" + v1.getValue() + "' and/or '" + v2.getValue() + "' are not of type 'NumberObject'");
	}

	return result;
}

Object subtract(Object& v1, Object& v2)
{
	Object result;

	if ( v1.Typename() == NumberObject::TYPENAME && v2.Typename() == NumberObject::TYPENAME ) {
		// none of our summands is a string
		float f1 = Tools::stringToFloat(v1.getValue());
		float f2 = Tools::stringToFloat(v2.getValue());

		result = NumberObject(Tools::toString(f1 - f2));
	}
	else {
		throw Utils::Exceptions::TypeMismatch("for subtraction: '" + v1.getValue() + "' and/or '" + v2.getValue() + "' are not of type 'NumberObject'");
	}

	return result;
}


}
}
