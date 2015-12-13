
// Header
#include "Types.h"

// Library includes

// Project includes

// Namespace declaration

namespace ObjectiveScript {


StringList provideAtomarTypes()
{
	StringList types;

	types.push_back(PROTOTYPE_TYPE);
	types.push_back("bool");
	//types.push_back("float");
	//types.push_back("int");
	types.push_back("number");
	types.push_back("string");
	types.push_back("void");

	return types;
}

StringList provideLanguageFeatures()
{
	StringList languageFeatures;

	languageFeatures.push_back("deprecated");
	languageFeatures.push_back("notimplemented");
	languageFeatures.push_back("stable");
	languageFeatures.push_back("unstable");

	return languageFeatures;
}

StringList provideKeyWords()
{
	StringList keywords;

	keywords.push_back("assert");
	keywords.push_back("break");
	keywords.push_back("case");
	keywords.push_back("catch");
	keywords.push_back("delete");
	keywords.push_back("else");
	keywords.push_back("except");
	keywords.push_back("extends");
	keywords.push_back("finally");
	keywords.push_back("for");
	keywords.push_back("if");
	keywords.push_back("import");
	keywords.push_back("new");
	keywords.push_back("print");
	keywords.push_back("return");
	keywords.push_back("switch");
	keywords.push_back("throw");
	keywords.push_back("try");
	keywords.push_back("while");
	keywords.push_back("using");

	return keywords;
}

StringList provideModifiers()
{
	StringList modifiers;

	modifiers.push_back("const");
	modifiers.push_back("final");
	modifiers.push_back("modify");
	modifiers.push_back("static");

	return modifiers;
}

StringList provideReservedWords()
{
	StringList reservedWords;
/*
	reservedWords.push_back("const");
	reservedWords.push_back("final");
	reservedWords.push_back("modify");
	reservedWords.push_back("static");
*/
	reservedWords.push_back("extends");
	reservedWords.push_back("interface");
	reservedWords.push_back("object");
	reservedWords.push_back("of");
	reservedWords.push_back("ref");
	reservedWords.push_back("prototype");
	reservedWords.push_back("val");

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
		result += " const";
	}
	switch ( param.access() ) {
		case Parameter::AccessMode::ByReference: result += " ByReference"; break;
		case Parameter::AccessMode::ByValue: result += " ByValue"; break;
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
