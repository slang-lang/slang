
// Header
#include "Types.h"

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


Algorithm::E Algorithm::convert(const std::string& v)
{
	if ( v == MODIFIER_HEURISTIC ) { return Algorithm::Heuristic; }
	else if ( v == MODIFIER_RECURSIVE ) { return Algorithm::Recursive; }

	return Algorithm::Unspecified;
}

std::string Algorithm::convert(Algorithm::E e)
{
	switch ( e ) {
		case Algorithm::Heuristic: return MODIFIER_HEURISTIC;
		case Algorithm::Recursive: return MODIFIER_RECURSIVE;
		case Algorithm::Unspecified: return UNKNOWN;
	}

	return UNKNOWN;
}


BluePrintType::E BluePrintType::convert(const std::string& v)
{
	if ( v == RESERVED_WORD_ENUM ) { return BluePrintType::Enum; }
	else if ( v == RESERVED_WORD_INTERFACE ) { return BluePrintType::Interface; }
	else if ( v == RESERVED_WORD_OBJECT ) { return BluePrintType::Object; }

	return BluePrintType::Unknown;
}

std::string BluePrintType::convert(BluePrintType::E e)
{
	switch ( e ) {
		case BluePrintType::Enum: return RESERVED_WORD_ENUM;
		case BluePrintType::Interface: return RESERVED_WORD_INTERFACE;
		case BluePrintType::Object: return RESERVED_WORD_OBJECT;
		case BluePrintType::Unknown: return UNKNOWN;
	}

	return UNKNOWN;
}


CheckedExceptions::E CheckedExceptions::convert(const std::string& v)
{
	if ( v == MODIFIER_NOTHROW ) { return CheckedExceptions::Nothrow; }
	else if ( v == MODIFIER_THROWS ) { return CheckedExceptions::Throw; }

	return CheckedExceptions::Unspecified;
}

std::string CheckedExceptions::convert(CheckedExceptions::E e)
{
	switch ( e ) {
		case CheckedExceptions::Nothrow: return MODIFIER_NOTHROW;
		case CheckedExceptions::Throw: return MODIFIER_THROWS;
		case CheckedExceptions::Unspecified: return UNKNOWN;
	}

	return UNKNOWN;
}


ImplementationType::E ImplementationType::convert(const std::string& v)
{
	if ( v == MODIFIER_ABSTRACT ) { return ImplementationType::Abstract; }
	else if ( v == "FullyImplemented" ) { return ImplementationType::FullyImplemented; }
	else if ( v == RESERVED_WORD_INTERFACE ) { return ImplementationType::Interface; }

	return ImplementationType::Unspecified;
}

std::string ImplementationType::convert(ImplementationType::E e)
{
	switch ( e ) {
		case ImplementationType::Abstract: return MODIFIER_ABSTRACT;
		case ImplementationType::FullyImplemented: return "FullyImplemented";
		case ImplementationType::Interface: return RESERVED_WORD_INTERFACE;
		case ImplementationType::Unspecified: return UNKNOWN;
	}

	return UNKNOWN;
}


LanguageFeatureState::E LanguageFeatureState::convert(const std::string& v)
{
	if ( v == LANGUAGE_FEATURE_DEPRECATED ) { return LanguageFeatureState::Deprecated; }
	else if ( v == LANGUAGE_FEATURE_NONE ) { return LanguageFeatureState::Stable; }
	else if ( v == LANGUAGE_FEATURE_NOTIMPLEMENTED ) { return LanguageFeatureState::NotImplemented; }
	else if ( v == LANGUAGE_FEATURE_STABLE ) { return LanguageFeatureState::Stable; }
	else if ( v == LANGUAGE_FEATURE_UNSTABLE ) { return LanguageFeatureState::Unstable; }

	return LanguageFeatureState::Unspecified;
}

std::string LanguageFeatureState::convert(LanguageFeatureState::E e)
{
	switch ( e ) {
		case LanguageFeatureState::Deprecated: return LANGUAGE_FEATURE_DEPRECATED;
		case LanguageFeatureState::NotImplemented: return LANGUAGE_FEATURE_NOTIMPLEMENTED;
		case LanguageFeatureState::Stable: return LANGUAGE_FEATURE_STABLE;
		case LanguageFeatureState::Unspecified: return UNKNOWN;
		case LanguageFeatureState::Unstable: return LANGUAGE_FEATURE_UNSTABLE;
	}

	return UNKNOWN;
}


MemoryLayout::E MemoryLayout::convert(const std::string& v)
{
	if ( v == MODIFIER_INSTANCE ) { return MemoryLayout::Instance; }
	else if ( v == MODIFIER_STATIC ) { return MemoryLayout::Static; }

	return MemoryLayout::Unspecified;
}

std::string MemoryLayout::convert(MemoryLayout::E e)
{
	switch ( e ) {
		case MemoryLayout::Instance: return MODIFIER_INSTANCE;
		case MemoryLayout::Static: return MODIFIER_STATIC;
		case MemoryLayout::Unspecified: return UNKNOWN;
	}

	return UNKNOWN;
}


Mutability::E Mutability::convert(const std::string& v)
{
	if ( v == MODIFIER_CONST ) { return Mutability::Const; }
	else if ( v == MODIFIER_MODIFY ) { return Mutability::Modify; }

	return Mutability::Unknown;
}

std::string Mutability::convert(Mutability::E e)
{
	switch ( e ) {
		case Mutability::Const: return MODIFIER_CONST;
		case Mutability::Modify: return MODIFIER_MODIFY;
		case Mutability::Unknown: return UNKNOWN;
	}

	return UNKNOWN;
}


Virtuality::E Virtuality::convert(const std::string& v)
{
	if ( v == MODIFIER_ABSTRACT ) { return Virtuality::Abstract; }
	else if ( v == MODIFIER_FINAL ) { return Virtuality::Final; }
	else if ( v == MODIFIER_VIRTUAL ) { return Virtuality::Virtual; }

	return Virtuality::Unknown;
}

std::string Virtuality::convert(Virtuality::E e)
{
	switch ( e ) {
		case Virtuality::Abstract: return MODIFIER_ABSTRACT;
		case Virtuality::Final: return MODIFIER_FINAL;
		case Virtuality::Virtual: return MODIFIER_VIRTUAL;
		case Virtuality::Unknown: return UNKNOWN;
	}

	return UNKNOWN;
}


}