
// Header
#include "Types.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/DoubleObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/NumberObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/UserObject.h>
#include <Core/BuildInObjects/VoidObject.h>

// Namespace declaration

namespace ObjectiveScript {


StringList provideAtomicTypes()
{
	StringList types;

	types.push_back(Runtime::BoolObject::TYPENAME);
	types.push_back(Runtime::DoubleObject::TYPENAME);
	types.push_back(Runtime::FloatObject::TYPENAME);
	types.push_back(Runtime::IntegerObject::TYPENAME);
	types.push_back(Runtime::NumberObject::TYPENAME);
	types.push_back(Runtime::StringObject::TYPENAME);
	types.push_back(Runtime::VoidObject::TYPENAME);

	return types;
}

StringList provideLanguageFeatures()
{
	StringList languageFeatures;

	languageFeatures.push_back(LANGUAGE_FEATURE_DEPRECATED);
	languageFeatures.push_back(LANGUAGE_FEATURE_NOTIMPLEMENTED);
	languageFeatures.push_back(LANGUAGE_FEATURE_STABLE);
	languageFeatures.push_back(LANGUAGE_FEATURE_UNSTABLE);

	return languageFeatures;
}

StringList provideKeyWords()
{
	StringList keywords;

	keywords.push_back(KEYWORD_ASSERT);
	keywords.push_back(KEYWORD_BREAK);
	keywords.push_back(KEYWORD_CASE);
	keywords.push_back(KEYWORD_CATCH);
	keywords.push_back(KEYWORD_CONTINUE);
	keywords.push_back(KEYWORD_DEFAULT);
	keywords.push_back(KEYWORD_DELETE);
	keywords.push_back(KEYWORD_ELSE);
	keywords.push_back(KEYWORD_EXIT);
	keywords.push_back(KEYWORD_FINALLY);
	keywords.push_back(KEYWORD_FOR);
	keywords.push_back(KEYWORD_IF);
	keywords.push_back(KEYWORD_NEW);
	keywords.push_back(KEYWORD_PRINT);
	keywords.push_back(KEYWORD_RETURN);
	keywords.push_back(KEYWORD_SWITCH);
	keywords.push_back(KEYWORD_THROW);
	keywords.push_back(KEYWORD_TRY);
	keywords.push_back(KEYWORD_WHILE);

	return keywords;
}

StringList provideModifiers()
{
	StringList modifiers;

	modifiers.push_back(MODIFIER_ABSTRACT);
	modifiers.push_back(MODIFIER_CONST);
	modifiers.push_back(MODIFIER_FINAL);
	modifiers.push_back(MODIFIER_MODIFY);
	modifiers.push_back(MODIFIER_RECURSIVE);

	return modifiers;
}

StringList providePredefinedIdentifiers()
{
	StringList identifiers;

	identifiers.push_back(IDENTIFIER_BASE);
	identifiers.push_back(IDENTIFIER_THIS);

	return identifiers;
}

StringList provideReservedWords()
{
	StringList reservedWords;

	reservedWords.push_back(RESERVED_WORD_BY_REFERENCE);
	reservedWords.push_back(RESERVED_WORD_BY_VALUE);
	reservedWords.push_back(RESERVED_WORD_ENUM);
	reservedWords.push_back(RESERVED_WORD_EXTENDS);
	reservedWords.push_back(RESERVED_WORD_IMPLEMENTS);
	reservedWords.push_back(RESERVED_WORD_IMPORT);
	reservedWords.push_back(RESERVED_WORD_INTERFACE);
	reservedWords.push_back(RESERVED_WORD_NAMESPACE);
	reservedWords.push_back(RESERVED_WORD_OBJECT);
	reservedWords.push_back(RESERVED_WORD_OPERATOR);
	reservedWords.push_back(RESERVED_WORD_PROTOTYPE);
	reservedWords.push_back(RESERVED_WORD_REPLICATES);
	reservedWords.push_back(RESERVED_WORD_SCOPE_OPERATOR);
	reservedWords.push_back(RESERVED_WORD_THROWS);
	reservedWords.push_back(RESERVED_WORD_USING);

	return reservedWords;
}

std::string toString(const Parameter& param)
{
	std::string result = param.type();
	if ( !param.name().empty() ) {
		result += " ";
		result += param.name();
	}
	else {
		result += " ";
		result += ANONYMOUS_OBJECT;
	}
	if ( param.isConst() ) {
		result += " ";
		result += MODIFIER_CONST;
	}
	switch ( param.access() ) {
		case Parameter::AccessMode::ByReference: result += " "; result += RESERVED_WORD_BY_REFERENCE; break;
		case Parameter::AccessMode::ByValue: result += " "; result += RESERVED_WORD_BY_VALUE; break;
		case Parameter::AccessMode::Unspecified: break;
	}
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

	for ( ParameterList::const_iterator it = list.begin(); it != list.end(); ++it ) {
		result += toString((*it));

		ParameterList::const_iterator copy = it;
		if ( ++copy != list.end() ) {
			result += ", ";
		}
	}

	return result;
}

std::string toString(const ReferencesList& list)
{
	std::string result;

	for ( ReferencesList::const_iterator it = list.begin(); it != list.end(); ++it ) {
		//result += it->getAddress();

		ReferencesList::const_iterator copy = it;
		if ( ++copy != list.end() ) {
			result += ", ";
		}
	}

	return result;
}

std::string toString(const StringList& list)
{
	std::string result;

	for ( StringList::const_iterator it = list.begin(); it != list.end(); ++it ) {
		result += (*it);

		StringList::const_iterator copy = it;
		if ( ++copy != list.end() ) {
			result += ", ";
		}
	}

	return result;
}

std::string toString(const TokenList& list)
{
	std::string result;

	for ( TokenIterator it = list.begin(); it != list.end(); ++it ) {
		result += it->content();

		TokenIterator copy = it;
		if ( ++copy != list.end() ) {
			result += ", ";
		}
	}

	return result;
}


}
