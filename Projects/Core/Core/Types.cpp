
// Header
#include "Types.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/BuildInTypes/BoolObject.h>
#include <Core/Runtime/BuildInTypes/DoubleObject.h>
#include <Core/Runtime/BuildInTypes/FloatObject.h>
#include <Core/Runtime/BuildInTypes/Int16Type.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/Int64Type.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/BuildInTypes/VoidObject.h>

// Namespace declaration

namespace Slang {


bool isAtomicType(const std::string& type)
{
	static const StringSet& atomicTypes = provideAtomicTypes();

	return atomicTypes.find(type) != atomicTypes.end();
}

StringSet provideAccessMode()
{
	static StringSet accessMode;

	accessMode.insert(RESERVED_WORD_BY_REFERENCE);
	accessMode.insert(RESERVED_WORD_BY_VALUE);

	return accessMode;
}

StringSet provideAtomicTypes()
{
	static StringSet types;

	types.insert(Runtime::BoolObject::TYPENAME);
	types.insert(Runtime::DoubleObject::TYPENAME);
	types.insert(Runtime::FloatObject::TYPENAME);
	types.insert(Runtime::Int16Type::TYPENAME);
	types.insert(Runtime::Int32Type::TYPENAME);
	types.insert(Runtime::Int64Type::TYPENAME);
	types.insert(Runtime::StringObject::TYPENAME);
	types.insert(Runtime::VoidObject::TYPENAME);

	return types;
}

StringSet provideLanguageFeatures()
{
	static StringSet languageFeatures;

	languageFeatures.insert(LANGUAGE_FEATURE_DEPRECATED);
	languageFeatures.insert(LANGUAGE_FEATURE_NOTIMPLEMENTED);
	languageFeatures.insert(LANGUAGE_FEATURE_STABLE);
	languageFeatures.insert(LANGUAGE_FEATURE_UNSTABLE);

	return languageFeatures;
}

StringSet provideKeyWords()
{
	static StringSet keywords;

	keywords.insert(KEYWORD_ASSERT);
	keywords.insert(KEYWORD_BREAK);
	keywords.insert(KEYWORD_CASE);
	keywords.insert(KEYWORD_CAST);
	keywords.insert(KEYWORD_CATCH);
	keywords.insert(KEYWORD_CONTINUE);
	keywords.insert(KEYWORD_COPY);
	keywords.insert(KEYWORD_DEFAULT);
	keywords.insert(KEYWORD_DELETE);
	keywords.insert(KEYWORD_ELSE);
	keywords.insert(KEYWORD_EXIT);
	keywords.insert(KEYWORD_FINALLY);
	keywords.insert(KEYWORD_FOR);
	keywords.insert(KEYWORD_FOREACH);
	keywords.insert(KEYWORD_IF);
	keywords.insert(KEYWORD_NEW);
	keywords.insert(KEYWORD_PRINT);
	keywords.insert(KEYWORD_RETURN);
	keywords.insert(KEYWORD_SWITCH);
	keywords.insert(KEYWORD_THROW);
	keywords.insert(KEYWORD_TRY);
	keywords.insert(KEYWORD_TYPEID);
	keywords.insert(KEYWORD_VAR);
	keywords.insert(KEYWORD_WHILE);

	return keywords;
}

StringSet provideMemoryLayout()
{
	static StringSet memoryLayout;

	memoryLayout.insert(MEMORY_LAYOUT_ABSTRACT);
	memoryLayout.insert(MEMORY_LAYOUT_FINAL);
	memoryLayout.insert(MEMORY_LAYOUT_OVERRIDE);
	memoryLayout.insert(MEMORY_LAYOUT_STATIC);
	memoryLayout.insert(MEMORY_LAYOUT_VIRTUAL);

	return memoryLayout;
}

StringSet provideModifier()
{
	static StringSet modifier;

	modifier.insert(MODIFIER_RECURSIVE);
	modifier.insert(MODIFIER_SEALED);
	modifier.insert(MODIFIER_THROWS);

	return modifier;
}

StringSet provideMutability()
{
	static StringSet mutability;

	mutability.insert(MUTABILITY_CONST);
	mutability.insert(MUTABILITY_MODIFY);

	return mutability;
}

StringSet provideReservedWords()
{
	static StringSet reservedWords;

	reservedWords.insert(RESERVED_WORD_ENUM);
	reservedWords.insert(RESERVED_WORD_EXTENDS);
	reservedWords.insert(RESERVED_WORD_IMPLEMENTS);
	reservedWords.insert(RESERVED_WORD_IMPORT);
	reservedWords.insert(RESERVED_WORD_INTERFACE);
	reservedWords.insert(RESERVED_WORD_NAMESPACE);
	reservedWords.insert(RESERVED_WORD_OBJECT);
	reservedWords.insert(RESERVED_WORD_OPERATOR);
	reservedWords.insert(RESERVED_WORD_REPLICATES);
	reservedWords.insert(RESERVED_WORD_SCOPE_OPERATOR);

	return reservedWords;
}

std::string toString(const Parameter& param)
{
	std::string result = param.type();
	if ( !result.empty() ) {
		result += " ";
		result += param.name();
	}
	else {
		result += " ";
		result += ANONYMOUS_OBJECT;
	}

	result += " " + Mutability::convert(param.mutability());
	result += " " + AccessMode::convert(param.access());

	if ( param.hasDefaultValue() ) {
		result += " = ";
		if ( param.type() == "string" ) {
			result += "\"" + param.value().toStdString() + "\"";
		}
		else {
			result += param.value().toStdString();
		}
	}

	return result;
}

std::string toString(const ParameterList& list)
{
	std::string result;

	for ( auto it = list.begin(); it != list.end(); ++it ) {
		result += toString((*it));

		auto copy = it;
		if ( ++copy != list.end() ) {
			result += ", ";
		}
	}

	return result;
}

std::string toString(const Runtime::ReferencesList& list)
{
	std::string result;

	for ( auto it = list.begin(); it != list.end(); ++it ) {
		//result += it->getAddress();

		auto copy = it;
		if ( ++copy != list.end() ) {
			result += ", ";
		}
	}

	return result;
}

std::string toString(const StringList& list)
{
	std::string result;

	for ( auto it = list.begin(); it != list.end(); ++it ) {
		result += (*it);

		auto copy = it;
		if ( ++copy != list.end() ) {
			result += ", ";
		}
	}

	return result;
}


}
