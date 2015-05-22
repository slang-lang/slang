
// Header
#include "Visibility.h"

// Library includes
#include <cassert>

// Project includes

// Namespace declarations


namespace ObjectiveScript {


const std::string Visibility::PrivateStr = "private";
const std::string Visibility::ProtectedStr = "protected";
const std::string Visibility::PublicStr = "public";


Visibility::E Visibility::convert(const std::string& v)
{
	if ( v == PrivateStr ) { return Visibility::Private; }
	else if ( v == ProtectedStr ) { return Visibility::Protected; }
	else if ( v == PublicStr ) { return Visibility::Public; }

	assert(!"invalid visibility!");
	return Visibility::Private;
}

std::string Visibility::convert(Visibility::E e)
{
	switch ( e ) {
		case Visibility::Private: return PrivateStr;
		case Visibility::Protected: return ProtectedStr;
		case Visibility::Public: return PublicStr;
	}

	assert(!"invalid visibility!");
	return "<unknown visibility>";
}


}
