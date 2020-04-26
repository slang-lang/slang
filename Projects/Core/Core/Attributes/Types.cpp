
// Header
#include "Types.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace Slang {


AccessMode::E AccessMode::convert(const std::string& v)
{
	if ( v == RESERVED_WORD_BY_REFERENCE ) { return AccessMode::ByReference; }

	return AccessMode::Unspecified;
}

std::string AccessMode::convert(AccessMode::E e)
{
	switch ( e ) {
		case AccessMode::ByReference: return RESERVED_WORD_BY_REFERENCE;
		case AccessMode::ByValue: return EMPTY;
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


BlueprintType::E BlueprintType::convert(const std::string& v)
{
	if ( v == RESERVED_WORD_ENUM ) { return BlueprintType::Enum; }
	else if ( v == RESERVED_WORD_INTERFACE ) { return BlueprintType::Interface; }
	else if ( v == RESERVED_WORD_OBJECT ) { return BlueprintType::Object; }

	return BlueprintType::Unknown;
}

std::string BlueprintType::convert(BlueprintType::E e)
{
	switch ( e ) {
		case BlueprintType::Enum: return RESERVED_WORD_ENUM;
		case BlueprintType::Interface: return RESERVED_WORD_INTERFACE;
		case BlueprintType::Object: return RESERVED_WORD_OBJECT;
		case BlueprintType::Unknown: return UNKNOWN;
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
		case LanguageFeatureState::Unspecified: return LANGUAGE_FEATURE_UNSPECIFIED;
		case LanguageFeatureState::Unstable: return LANGUAGE_FEATURE_UNSTABLE;
	}

	return UNKNOWN;
}


MemoryLayout::E MemoryLayout::convert(const std::string& v)
{
	if (v == MEMORY_LAYOUT_ABSTRACT ) { return MemoryLayout::Abstract; }
	else if (v == MEMORY_LAYOUT_FINAL ) { return MemoryLayout::Final; }
	else if (v == MEMORY_LAYOUT_OVERRIDE ) { return MemoryLayout::Override; }
	else if (v == MEMORY_LAYOUT_STATIC ) { return MemoryLayout::Static; }
	else if (v == MEMORY_LAYOUT_VIRTUAL ) { return MemoryLayout::Virtual; }

	return MemoryLayout::Unspecified;
}

std::string MemoryLayout::convert(MemoryLayout::E e)
{
	switch ( e ) {
		case MemoryLayout::Abstract: return MEMORY_LAYOUT_ABSTRACT;
		case MemoryLayout::Final: return MEMORY_LAYOUT_FINAL;
		case MemoryLayout::Override: return MEMORY_LAYOUT_OVERRIDE;
		case MemoryLayout::Static: return MEMORY_LAYOUT_STATIC;
		case MemoryLayout::Virtual: return MEMORY_LAYOUT_VIRTUAL;
		case MemoryLayout::Unspecified: return UNKNOWN;
	}

	return UNKNOWN;
}


Mutability::E Mutability::convert(const std::string& v)
{
	if (v == MUTABILITY_CONST ) { return Mutability::Const; }
	else if (v == MUTABILITY_MODIFY ) { return Mutability::Modify; }

	return Mutability::Unknown;
}

std::string Mutability::convert(Mutability::E e)
{
	switch ( e ) {
		case Mutability::Const: return MUTABILITY_CONST;
		case Mutability::Modify: return MUTABILITY_MODIFY;
		case Mutability::Unknown: return UNKNOWN;
	}

	return UNKNOWN;
}


}
