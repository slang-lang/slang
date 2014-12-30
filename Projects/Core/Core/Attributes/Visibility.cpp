
// Header
#include "Visibility.h"

// Library includes
#include <cassert>

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Visibility::E Visibility::convert(const std::string& v)
{
	if ( v == "private" ) { return Visibility::Private; }
	else if ( v == "protected" ) { return Visibility::Protected; }
	else if ( v == "public" ) { return Visibility::Public; }

	assert(!"invalid visibility!");
	return Visibility::Private;
}

std::string Visibility::convert(Visibility::E e)
{
	switch ( e ) {
		case Visibility::Private: return "private";
		case Visibility::Protected: return "protected";
		case Visibility::Public: return "public";
	}

	return "<unknown visibility>";
}


}
