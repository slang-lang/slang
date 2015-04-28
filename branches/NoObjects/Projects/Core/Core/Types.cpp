
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
	types.push_back("float");
	types.push_back("int");
	types.push_back("number");
	types.push_back("string");
	types.push_back("void");

	return types;
}

StringList provideKeyWords()
{
	StringList keywords;

	keywords.push_back("assert");
	keywords.push_back("break");
	keywords.push_back("breakpoint");
	keywords.push_back("case");
	keywords.push_back("delete");
	keywords.push_back("else");
	keywords.push_back("extends");
	keywords.push_back("for");
	keywords.push_back("if");
	keywords.push_back("import");
	keywords.push_back("new");
	keywords.push_back("print");
	keywords.push_back("return");
	keywords.push_back("switch");
	keywords.push_back("while");

	return keywords;
}

StringList provideReservedWords()
{
	StringList reservedWords;

	reservedWords.push_back("const");
	reservedWords.push_back("extends");
	reservedWords.push_back("interface");
	reservedWords.push_back("object");
	reservedWords.push_back("of");
	reservedWords.push_back("static");

	return reservedWords;
}

std::string toString(const ParameterList& list)
{
	std::string result;

	for ( ParameterList::const_iterator it = list.begin(); it != list.end(); ++it ) {
		result = it->type() + " " + it->name() + " = " + it->value();

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
		//result += (*it).getAddress();

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
		result += (*it).content();

		TokenIterator copy = it;
		if ( ++copy != list.end() ) {
			result += ", ";
		}
	}

	return result;
}

/* deprecated
std::string toString(const VariablesList& list)
{
	std::string result;

	for ( VariablesList::const_iterator it = list.begin(); it != list.end(); ++it ) {
		result += (*it).type() + " " + (*it).name() + " = " + (*it).value();

		VariablesList::const_iterator copy = it;
		if ( ++copy != list.end() ) {
			result += ", ";
		}
	}

	return result;
}
*/


}
