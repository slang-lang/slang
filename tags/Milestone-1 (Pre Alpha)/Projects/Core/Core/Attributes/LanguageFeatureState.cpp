
// Header
#include "LanguageFeatureState.h"

// Library includes
#include <cassert>

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {


LanguageFeatureState::E LanguageFeatureState::convert(const std::string& v)
{
	if ( v == LANGUAGE_FEATURE_DEPRECATED ) { return LanguageFeatureState::Deprecated; }
	else if ( v == LANGUAGE_FEATURE_NONE ) { return LanguageFeatureState::Stable; }
	else if ( v == LANGUAGE_FEATURE_NOTIMPLEMENTED ) { return LanguageFeatureState::NotImplemented; }
	else if ( v == LANGUAGE_FEATURE_STABLE ) { return LanguageFeatureState::Stable; }
	else if ( v == LANGUAGE_FEATURE_UNKNOWN ) { return LanguageFeatureState::Unknown; }
	else if ( v == LANGUAGE_FEATURE_UNSTABLE ) { return LanguageFeatureState::Unstable; }

	return LanguageFeatureState::Unknown;
}

std::string LanguageFeatureState::convert(LanguageFeatureState::E e)
{
	switch ( e ) {
		case LanguageFeatureState::Deprecated: return LANGUAGE_FEATURE_DEPRECATED;
		case LanguageFeatureState::NotImplemented: return LANGUAGE_FEATURE_NOTIMPLEMENTED;
		case LanguageFeatureState::Stable: return LANGUAGE_FEATURE_STABLE;
		case LanguageFeatureState::Unknown: return LANGUAGE_FEATURE_UNKNOWN;
		case LanguageFeatureState::Unstable: return LANGUAGE_FEATURE_UNSTABLE;
	}

	return LANGUAGE_FEATURE_UNKNOWN;
}


}
