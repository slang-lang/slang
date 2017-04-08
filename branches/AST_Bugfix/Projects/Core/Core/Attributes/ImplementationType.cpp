
// Header
#include "ImplementationType.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {


ImplementationType::E ImplementationType::convert(const std::string& v)
{
	if ( v == MODIFIER_ABSTRACT ) { return ImplementationType::Abstract; }
	else if ( v == "ForwardDeclaration" ) { return ImplementationType::ForwardDeclaration; }
	else if ( v == "FullyImplemented" ) { return ImplementationType::FullyImplemented; }
	else if ( v == RESERVED_WORD_INTERFACE ) { return ImplementationType::Interface; }
	else if ( v == UNKNOWN ) { return ImplementationType::Unknown; }

	return ImplementationType::Unknown;
}

std::string ImplementationType::convert(ImplementationType::E e)
{
	switch ( e ) {
		case ImplementationType::Abstract: return MODIFIER_ABSTRACT;
		case ImplementationType::ForwardDeclaration: return "ForwardDeclaration";
		case ImplementationType::FullyImplemented: return "FullyImplemented";
		case ImplementationType::Interface: return RESERVED_WORD_INTERFACE;
		case ImplementationType::Unknown: return UNKNOWN;
	}

	return UNKNOWN;
}


}
