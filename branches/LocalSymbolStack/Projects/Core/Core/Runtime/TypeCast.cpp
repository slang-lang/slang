
// Header
#include "TypeCast.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/VoidObject.h>
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
