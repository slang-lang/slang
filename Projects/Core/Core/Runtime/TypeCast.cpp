
// Header
#include "TypeCast.h"

// Library includes

// Project includes
#include <Core/Runtime/BuildInTypes/BoolObject.h>
#include <Core/Runtime/BuildInTypes/DoubleObject.h>
#include <Core/Runtime/BuildInTypes/EnumerationObject.h>
#include <Core/Runtime/BuildInTypes/FloatObject.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/BuildInTypes/VoidObject.h>
#include <Core/Runtime/Exceptions.h>
#include <Utils.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


void typecast(Object *base, const std::string& targetType)
{
	if ( !base ) {
		OSerror("cannot cast null pointer");
		throw Runtime::Exceptions::NullPointerException("cannot cast null pointer");
	}
	if ( targetType.empty() ) {
		OSerror("invalid cast target type");
		throw Runtime::Exceptions::TypecastException("invalid cast target type");
	}

	if ( targetType == BoolObject::TYPENAME ) {
		BoolObject tmp(*base);

		base->assign(tmp);
	}
	else if ( targetType == DoubleObject::TYPENAME ) {
		DoubleObject tmp(*base);

		base->assign(tmp);
	}
	else if ( targetType == EnumerationObject::TYPENAME ) {
		assert(! "implement me");

/*
		EnumerationObject tmp(*base);

		base->assign(tmp);
 */
	}
	else if ( targetType == FloatObject::TYPENAME ) {
		FloatObject tmp(*base);

		base->assign(tmp);
	}
	else if ( targetType == IntegerObject::TYPENAME ) {
		IntegerObject tmp(*base);

		base->assign(tmp);
	}
	else if ( targetType == StringObject::TYPENAME ) {
		StringObject tmp(*base);

		base->assign(tmp);
	}
	else if ( targetType == VoidObject::TYPENAME ) {
		VoidObject tmp(*base);

		base->assign(tmp);
	}

	// override outerface type
	base->setQualifiedOuterface(targetType);
}
}


}

