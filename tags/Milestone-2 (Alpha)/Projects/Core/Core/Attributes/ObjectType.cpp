
// Header
#include "ObjectType.h"

// Library includes
#include <string>

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {


ObjectType::E ObjectType::convert(const std::string& v)
{
	if ( v == RESERVED_WORD_ENUM ) { return ObjectType::Enum; }
	else if ( v == RESERVED_WORD_INTERFACE ) { return ObjectType::Interface; }
	else if ( v == RESERVED_WORD_OBJECT ) { return ObjectType::Object; }
	else if ( v == UNKNOWN ) { return ObjectType::Unknown; }

	return ObjectType::Unknown;
}

std::string ObjectType::convert(ObjectType::E e)
{
	switch ( e ) {
		case ObjectType::Enum: return RESERVED_WORD_ENUM;
		case ObjectType::Interface: return RESERVED_WORD_INTERFACE;
		case ObjectType::Object: return RESERVED_WORD_OBJECT;
		case ObjectType::Unknown: return UNKNOWN;
	}

	return UNKNOWN;
}


}
