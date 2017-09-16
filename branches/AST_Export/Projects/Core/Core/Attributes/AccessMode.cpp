
// Header
#include "AccessMode.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {


AccessMode::E AccessMode::convert(const std::string& v)
{
	if ( v == RESERVED_WORD_BY_REFERENCE ) { return AccessMode::ByReference; }
	else if ( v == RESERVED_WORD_BY_VALUE ) { return AccessMode::ByValue; }

	return AccessMode::Unspecified;
}

std::string AccessMode::convert(AccessMode::E e)
{
	switch ( e ) {
		case AccessMode::ByReference: return RESERVED_WORD_BY_REFERENCE;
		case AccessMode::ByValue: return RESERVED_WORD_BY_VALUE;
		case AccessMode::Unspecified: return UNKNOWN;
	}

	return UNKNOWN;
}


}
