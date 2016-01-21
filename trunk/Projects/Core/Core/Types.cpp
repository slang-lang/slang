
// Header
#include "Types.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/FloatObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/NumberObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/BuildInObjects/UserObject.h>
#include <Core/BuildInObjects/VoidObject.h>

// Namespace declaration

namespace ObjectiveScript {


StringList provideAtomarTypes()
{
	StringList types;

	types.push_back(PROTOTYPE_TYPE);
	types.push_back(Runtime::BoolObject::TYPENAME);
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
	keywords.push_back(KEYWORD_CONTINUE);
	keywords.push_back(KEYWORD_DELETE);
	keywords.push_back(KEYWORD_ELSE);
	keywords.push_back(KEYWORD_FOR);
	keywords.push_back(KEYWORD_IF);
	keywords.push_back(KEYWORD_IMPORT);
	keywords.push_back(KEYWORD_NEW);
	keywords.push_back(KEYWORD_PRINT);
	keywords.push_back(KEYWORD_RETURN);
	keywords.push_back(KEYWORD_SWITCH);
	keywords.push_back(KEYWORD_WHILE);
	keywords.push_back("catch");
	keywords.push_back("except");
	keywords.push_back("finally");
	keywords.push_back("throw");
	keywords.push_back("try");

	return keywords;
}

StringList provideModifiers()
{
	StringList modifiers;

	modifiers.push_back(MODIFIER_CONST);
	modifiers.push_back(MODIFIER_FINAL);
	modifiers.push_back(MODIFIER_MODIFY);

	return modifiers;
}

StringList provideReservedWords()
{
	StringList reservedWords;

	reservedWords.push_back(RESERVED_WORD_BY_REFERENCE);
	reservedWords.push_back(RESERVED_WORD_BY_VALUE);
	reservedWords.push_back(RESERVED_WORD_EXTENDS);
	reservedWords.push_back(RESERVED_WORD_INTERFACE);
	reservedWords.push_back(RESERVED_WORD_OBJECT);
	reservedWords.push_back(RESERVED_WORD_OPERATOR);
	reservedWords.push_back(RESERVED_WORD_PROTOTYPE);
	reservedWords.push_back(RESERVED_WORD_USING);
	reservedWords.push_back("of");

	return reservedWords;
}

std::string toString(const Parameter& param)
{
	std::string result = param.type();
	if ( !param.name().empty() ) {
		result += " " + param.name();
	}
	else {
		result += " <unnamed object>";
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
	result += " = ";
	result += param.value();

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
