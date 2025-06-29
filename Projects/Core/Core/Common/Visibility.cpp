
// Header
#include "Visibility.h"

// Library includes
#include <cassert>

// Project includes

// Namespace declarations


namespace Slang {


const std::string Visibility::DesigntimeStr = "Designtime";
const std::string Visibility::PrivateStr = "private";
const std::string Visibility::ProtectedStr = "protected";
const std::string Visibility::PublicStr = "public";


Visibility::E Visibility::convert(const std::string& v)
{
	if ( v == DesigntimeStr ) return Visibility::Designtime;
	if ( v == PrivateStr )    return Visibility::Private;
	if ( v == ProtectedStr )  return Visibility::Protected;
	if ( v == PublicStr )     return Visibility::Public;

	assert(!"invalid visibility!");
	return Visibility::Private;
}

std::string Visibility::convert(Visibility::E e)
{
	switch ( e ) {
		case Visibility::Designtime: return DesigntimeStr;
		case Visibility::Private: return PrivateStr;
		case Visibility::Protected: return ProtectedStr;
		case Visibility::Public: return PublicStr;
	}

	assert(!"invalid visibility!");
	return "<unknown visibility>";
}


}
