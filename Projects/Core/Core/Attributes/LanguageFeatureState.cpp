
// Header
#include "LanguageFeatureState.h"

// Library includes
#include <cassert>

// Project includes

// Namespace declarations


namespace ObjectiveScript {


LanguageFeatureState::E LanguageFeatureState::convert(const std::string& v)
{
	if ( v == "deprecated" ) { return LanguageFeatureState::Deprecated; }
	else if ( v == "notimplemented" ) { return LanguageFeatureState::NotImplemented; }
	else if ( v == "stable" ) { return LanguageFeatureState::Stable; }
	else if ( v == "unknown" ) { return LanguageFeatureState::Unknown; }
	else if ( v == "unstable" ) { return LanguageFeatureState::Unstable; }

	return LanguageFeatureState::Stable;
}

std::string LanguageFeatureState::convert(LanguageFeatureState::E e)
{
	switch ( e ) {
		case LanguageFeatureState::Deprecated: return "deprecated";
		case LanguageFeatureState::NotImplemented: return "notimplemented";
		case LanguageFeatureState::Stable: return "stable";
		case LanguageFeatureState::Unknown: return "unknown";
		case LanguageFeatureState::Unstable: return "unstable";
	}

	return "<unknown language feature state>";
}


}
