
// Header
#include "TypeCast.h"

// Library includes

// Project includes
#include <Core/Runtime/BuildInTypes/BoolType.h>
#include <Core/Runtime/BuildInTypes/DoubleType.h>
#include <Core/Runtime/BuildInTypes/EnumerationType.h>
#include <Core/Runtime/BuildInTypes/FloatType.h>
#include <Core/Runtime/BuildInTypes/Int16Type.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/Int64Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/BuildInTypes/VoidType.h>
#include <Core/Runtime/Exceptions.h>
#include <Logger/Logger.h>

// Namespace declarations


namespace Slang {
namespace Runtime {


void typecast(Object *base, const std::string& targetType)
{
	if ( !base ) {
		OSerror("cannot cast null pointer");
		throw Exceptions::NullPointerException("cannot cast null pointer");
	}
	if ( targetType.empty() ) {
		OSerror("invalid cast target type");
		throw Exceptions::TypecastException("invalid cast target type");
	}

	if ( targetType == BoolType::TYPENAME ) {
		BoolType tmp(*base);

		base->assign(tmp);
	}
	else if ( targetType == DoubleType::TYPENAME ) {
		DoubleType tmp(*base);

		base->assign(tmp);
	}
	else if ( targetType == EnumerationType::TYPENAME ) {
		assert(! "implement me");

/*
		EnumerationType tmp(*base);

		base->assign(tmp);
 */
	}
	else if ( targetType == FloatType::TYPENAME ) {
		FloatType tmp(*base);

		base->assign(tmp);
	}
	else if ( targetType == Int16Type::TYPENAME ) {
		Int16Type tmp(*base);

		base->assign(tmp);
	}
	else if ( targetType == Int32Type::TYPENAME ) {
		Int32Type tmp(*base);

		base->assign(tmp);
	}
	else if ( targetType == Int64Type::TYPENAME ) {
		Int64Type tmp(*base);

		base->assign(tmp);
	}
	else if ( targetType == StringType::TYPENAME ) {
		StringType tmp(*base);

		base->assign(tmp);
	}
	else if ( targetType == VoidType::TYPENAME ) {
		VoidType tmp(*base);

		base->assign(tmp);
	}

	// override outerface type
	base->setQualifiedOuterface(targetType);
}
}


}
