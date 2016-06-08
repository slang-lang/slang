
// Header
#include "Mutability.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {


Mutability::E Mutability::convert(const std::string& v)
{
	if ( v == MODIFIER_CONST ) { return Mutability::Const; }
	else if ( v == MODIFIER_FINAL ) { return Mutability::Final; }
	else if ( v == MODIFIER_MODIFY ) { return Mutability::Modify; }
	else if ( v == MODIFIER_UNKNOWN ) { return Mutability::Unknown; }

	return Mutability::Unknown;
}

std::string Mutability::convert(Mutability::E e)
{
	switch ( e ) {
		case Mutability::Const: return MODIFIER_CONST;
		case Mutability::Final: return MODIFIER_FINAL;
		case Mutability::Modify: return MODIFIER_MODIFY;
		case Mutability::Unknown: return MODIFIER_UNKNOWN;
	}

	return MODIFIER_UNKNOWN;
}


}
