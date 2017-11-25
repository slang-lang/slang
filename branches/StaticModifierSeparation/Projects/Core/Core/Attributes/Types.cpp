
// Header
#include "Types.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {


MemoryLayout::E MemoryLayout::convert(const std::string& v)
{
	if ( v == MODIFIER_INSTANCE ) { return MemoryLayout::Instance; }
	else if ( v == MODIFIER_STATIC ) { return MemoryLayout::Static; }

	return MemoryLayout::Unknown;
}

std::string MemoryLayout::convert(MemoryLayout::E e)
{
	switch ( e ) {
		case MemoryLayout::Instance: return MODIFIER_INSTANCE;
		case MemoryLayout::Static: return MODIFIER_STATIC;
		case MemoryLayout::Unknown: return UNKNOWN;
	}

	return UNKNOWN;
}


Virtuality::E Virtuality::convert(const std::string& v)
{
	if ( v == MODIFIER_FINAL ) { return Virtuality::Final; }
	else if ( v == MODIFIER_VIRTUAL ) { return Virtuality::Virtual; }

	return Virtuality::Unknown;
}

std::string Virtuality::convert(Virtuality::E e)
{
	switch ( e ) {
		case Virtuality::Final: return MODIFIER_FINAL;
		case Virtuality::Virtual: return MODIFIER_VIRTUAL;
		case Virtuality::Unknown: return UNKNOWN;
	}

	return UNKNOWN;
}


}
