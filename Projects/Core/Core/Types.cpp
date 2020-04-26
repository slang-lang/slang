
// Header
#include "Types.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Runtime/BuildInTypes/BoolObject.h>
#include <Core/Runtime/BuildInTypes/DoubleObject.h>
#include <Core/Runtime/BuildInTypes/FloatObject.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/BuildInTypes/VoidObject.h>

// Namespace declaration

namespace Slang {


bool isAtomicType(const std::string& type)
{
	static const StringSet& atomicTypes = provideAtomicTypes();

	auto it = atomicTypes.find(type);

	return it != atomicTypes.end();
}

StringSet provideAtomicTypes()
{
	static StringSet types;

	types.insert(Runtime::BoolObject::TYPENAME);
	types.insert(Runtime::DoubleObject::TYPENAME);
	types.insert(Runtime::FloatObject::TYPENAME);
	types.insert(Runtime::IntegerObject::TYPENAME);
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

StringSet provideModifier()
{
	static StringSet modifier;

	modifier.insert(MODIFIER_ABSTRACT);
	//modifier.insert(MUTABILITY_CONST);
	modifier.insert(MODIFIER_FINAL);
	//modifier.insert(MUTABILITY_MODIFY);
	modifier.insert(MODIFIER_OVERRIDE);
	modifier.insert(MODIFIER_RECURSIVE);
	modifier.insert(MODIFIER_SEALED);
	modifier.insert(MODIFIER_STATIC);
	modifier.insert(MODIFIER_THROWS);
	modifier.insert(MODIFIER_VIRTUAL);

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

	reservedWords.insert(RESERVED_WORD_BY_REFERENCE);
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

	result += " "; result += Mutability::convert(param.mutability());
	result += " "; result += AccessMode::convert(param.access());

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
