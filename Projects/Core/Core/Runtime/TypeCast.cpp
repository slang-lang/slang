
// Header
#include "TypeCast.h"

// Library includes
#include <string>

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/GenericObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/NumberObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/UserObject.h>
#include <Core/BuildInObjects/VoidObject.h>
#include <Core/Object.h>
#include <Core/Utils/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


void typecast(Object *base, const std::string& type)
{
	if ( !base ) {
		throw Utils::Exceptions::NullPointer("cannot cast null pointer");
	}
	if ( type.empty() ) {
		throw Utils::Exceptions::Exception("invalid cast target type");
	}

	if ( type == GenericObject::TYPENAME ) {
/*
		GenericObject tmp(*base);

		*base = tmp;
*/
		base->overrideTypename(GenericObject::TYPENAME);
	}
	else if ( type == BoolObject::TYPENAME ) {
		BoolObject tmp(*base);

		*base = tmp;
	}
	else if ( type == DoubleObject::TYPENAME ) {
		DoubleObject tmp(*base);

		*base = tmp;
	}
	else if ( type == FloatObject::TYPENAME ) {
		FloatObject tmp(*base);

		*base = tmp;
	}
	else if ( type == IntegerObject::TYPENAME ) {
		IntegerObject tmp(*base);

		*base = tmp;
	}
	else if ( type == NumberObject::TYPENAME ) {
		NumberObject tmp(*base);

		*base = tmp;
	}
	else if ( type == StringObject::TYPENAME ) {
		StringObject tmp(*base);

		*base = tmp;
	}
	else if ( type == VoidObject::TYPENAME ) {
		VoidObject tmp(*base);

		*base = tmp;
	}
	else {
		throw Utils::Exceptions::NotImplemented("type cast from type " + base->Typename() + " to type " + type);

/*
		ParameterList params;
		params.push_back(
			Parameter(base->getName(), base->Typename(), base->getValue(), false, base->isConst(), Parameter::AccessMode::ByReference, base)
		);

		Object other;
		other.execute(base, "operator=", params, 0);
*/
	}
}
}


}

