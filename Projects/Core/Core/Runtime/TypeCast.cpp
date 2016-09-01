
// Header
#include "TypeCast.h"

// Library includes

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
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


void typecast(Object *base, const std::string& targetType, Repository *repository)
{
	if ( !base ) {
		OSerror("cannot cast null pointer");
		throw Utils::Exceptions::NullPointer("cannot cast null pointer");
	}
	if ( !repository ) {
		OSerror("invalid repository provided");
		throw Utils::Exceptions::NullPointer("invalid repository provided");
	}
	if ( targetType.empty() ) {
		OSerror("invalid cast target type");
		throw Utils::Exceptions::Exception("invalid cast target type");
	}


	if ( targetType == GenericObject::TYPENAME ) {
		base->setQualifiedTypename(GenericObject::TYPENAME);
		base->setTypename(GenericObject::TYPENAME);
	}
	else if ( targetType == BoolObject::TYPENAME ) {
		BoolObject tmp(*base);

		*base = tmp;
	}
	else if ( targetType == DoubleObject::TYPENAME ) {
		DoubleObject tmp(*base);

		*base = tmp;
	}
	else if ( targetType == FloatObject::TYPENAME ) {
		FloatObject tmp(*base);

		*base = tmp;
	}
	else if ( targetType == IntegerObject::TYPENAME ) {
		IntegerObject tmp(*base);

		*base = tmp;
	}
	else if ( targetType == NumberObject::TYPENAME ) {
		NumberObject tmp(*base);

		*base = tmp;
	}
	else if ( targetType == StringObject::TYPENAME ) {
		StringObject tmp(*base);

		*base = tmp;
	}
	else if ( targetType == VoidObject::TYPENAME ) {
		VoidObject tmp(*base);

		*base = tmp;
	}
	else {
		Object tmp(*base);
		tmp.setQualifiedTypename(targetType);
		tmp.setTypename(targetType);

		*base = tmp;
	}
}
}


}

