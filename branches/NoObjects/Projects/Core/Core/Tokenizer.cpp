
// Header
#include "Tokenizer.h"

// Library includes

// Project includes
#include <Core/Keywords/for.h>
#include <Core/Keywords/if.h>
#include <Core/Keywords/print.h>
#include <Core/Keywords/return.h>
#include <Core/Utils/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {


const std::string CONTROLCHARS	= "#,;:=()[]{}+-*/&'\" ";
const std::string DELIMITERS	= "#,;:=()[]{}+-*/&'\"\t\n\r ";
const std::string WHITESPACES	= "\t\n\r ";


Tokenizer::Tokenizer(const std::string& content)
: mContent(content)
{
	mKeywords = provideKeyWords();
	mReservedWords = provideReservedWords();
	mTypes = provideAtomarTypes();
}

void Tokenizer::addIdentifier(const std::string& identifier)
{
	for ( StringList::const_iterator it = mIdentifiers.begin(); it != mIdentifiers.end(); ++it ) {
		if ( (*it) == identifier ) {
			// already announced identifier
			return;
		}
	}

	mIdentifiers.push_back(identifier);
}

void Tokenizer::addToken(const Token& token)
{
	if ( token.content().empty() && token.type() == Token::Type::UNKNOWN ) {
		// ignore this non-existing token
		return;
	}

	// add only valid tokens to our token list
	mTokens.push_back(token);
}

void Tokenizer::addType(const std::string& type)
{
	for ( StringList::const_iterator it = mTypes.begin(); it != mTypes.end(); ++it ) {
		if ( (*it) == type ) {
			// already announced identifier
			return;
		}
	}

	mTypes.push_back(type);
}

void Tokenizer::classify()
{
	// 1) check for a keyword
	// 2) get its' "content"
	// 3) and fill it up

	std::list<Keywords::AKeyword> keywords;

	TokenIterator token = mTokens.begin();
	while ( token != mTokens.end() ) {
		if ( (*token).content() == "for" ) {
			// if the next token is no '(' throw a synthax error exception
			if ( (*++token).type() != Token::Type::PARENTHESIS_OPEN ) {
				throw Utils::SyntaxError("'(' expected but '" + (*token).content() + "' found", token->position());
			}

		}
		else if ( (*token).content() == "if" ) {
			// if the next token is no '(' throw a synthax error exception
			if ( (*++token).type() != Token::Type::PARENTHESIS_OPEN ) {
				throw Utils::SyntaxError("'(' expected but '" + (*token).content() + "' found", token->position());
			}

		}
		else if ( (*token).content() == "print" ) {
			// if the next token is no '(' throw a synthax error exception
			if ( (*++token).type() != Token::Type::PARENTHESIS_OPEN ) {
				throw Utils::SyntaxError("'(' expected but '" + (*token).content() + "' found", token->position());
			}

			token++;

			TokenList list;

			int parenthesis = 0;
			while ( token != mTokens.end() || parenthesis > 0 ) {
				if ( (*token).type() == Token::Type::PARENTHESIS_CLOSE ) {
					if ( parenthesis == 0 ) {
						break;
					}
					parenthesis--;
				}
				else if ( (*token).type() == Token::Type::PARENTHESIS_OPEN ) {
					parenthesis++;
				}

				list.push_back((*token));
				token++;
			}

			if ( (*++token).type() != Token::Type::SEMICOLON ) {
				throw Utils::SyntaxError("';' expected but '" + (*token).content() + "' found", token->position());
			}

			Keywords::Print p;
			p.tokens(list);

			keywords.push_back(p);
		}
		else if ( (*token).content() == "return" ) {
			// this one is difficult, there can be virtually an token after a return keyword...
			// so pick up all tokens until we find a semicolon

			token++;

			TokenList list;

			int parenthesis = 0;
			while ( token != mTokens.end() || parenthesis > 0 || (*token).type() != Token::Type::SEMICOLON ) {
				if ( (*token).type() == Token::Type::SEMICOLON ) {
					break;
				}
				if ( (*token).type() == Token::Type::PARENTHESIS_CLOSE ) {
					if ( parenthesis == 0 ) {
						break;
					}
					parenthesis--;
				}
				else if ( (*token).type() == Token::Type::PARENTHESIS_OPEN ) {
					parenthesis++;
				}

				list.push_back((*token));
				token++;
			}

			if ( (*token).type() != Token::Type::SEMICOLON ) {
				throw Utils::SyntaxError("';' expected but '" + (*token).content() + "' found", token->position());
			}

			Keywords::Return r;
			r.tokens(list);

			keywords.push_back(r);
		}

		token++;
	}



}

Token Tokenizer::createToken(const std::string& con, const Utils::Position& pos)
{
	std::string content = con;

	Token::Type::E type = Token::Type::IDENTIFER;

	if ( content == "," ) { type = Token::Type::COLON; }
	else if ( content == "." ) { type = Token::Type::DOT; }
	else if ( content == ";" ) { type = Token::Type::SEMICOLON; }
	else if ( content == "'" ) { type = Token::Type::QUOTATION_SINGLE; }
	else if ( content == "\"" ) { type = Token::Type::QUOTATION_DOUBLE; }
	else if ( content == "[" ) { type = Token::Type::BRACKET_OPEN; }
	else if ( content == "]" ) { type = Token::Type::BRACKET_CLOSE; }
	else if ( content == "{" ) { type = Token::Type::BRACKET_CURLY_OPEN; }
	else if ( content == "}" ) { type = Token::Type::BRACKET_CURLY_CLOSE; }
	else if ( content == ">" ) { type = Token::Type::COMPARE_GREATER; }
	else if ( content == "<" ) { type = Token::Type::COMPARE_LESS; }
	else if ( content == "=" ) { type = Token::Type::EQUAL; }
	else if ( content == "(" ) { type = Token::Type::PARENTHESIS_OPEN; }
	else if ( content == ")" ) { type = Token::Type::PARENTHESIS_CLOSE; }
	else if ( content == "+" ) { type = Token::Type::MATH_ADD; }
	else if ( content == "/" ) { type = Token::Type::MATH_DIV; }
	else if ( content == "*" ) { type = Token::Type::MATH_MULTI; }
	else if ( content == "-" ) { type = Token::Type::MATH_SUBTRACT; }
	else if ( content == "&" ) { type = Token::Type::STRING_ADD; }
	else if ( content == "case" ) { type = Token::Type::CASE; }
	else if ( isBoolean(content) ) { type = Token::Type::BOOLEAN; }
	else if ( isDigit(content) ) { type = Token::Type::CONSTANT; }
	else if ( isIdentifer(content) ) { type = Token::Type::IDENTIFER; }
	else if ( isKeyword(content) ) { type = Token::Type::KEYWORD; }
	else if ( isLanguageFeature(content) ) { type = Token::Type::LANGUAGEFEATURE; }
	else if ( isLiteral(content) ) {
		// remove leading and trailing (", ') quotation marks (", ')
		type = Token::Type::LITERAL;
		content = con.substr(1, con.length() - 2);
	}
	else if ( isReservedWord(content) ) { type = Token::Type::RESERVED; }
	else if ( isType(content) ) { type = Token::Type::TYPE; }
	else if ( isVisibility(content) ) { type = Token::Type::VISIBILITY; }
	else if ( isWhiteSpace(content) ) { type = Token::Type::WHITESPACE; }

	Token token(type, content, pos);
	token.setOptional(type == Token::Type::LANGUAGEFEATURE);
	return token;
}

bool Tokenizer::isBoolean(const std::string& token) const
{
	return (token == "false" || token == "true");
}

bool Tokenizer::isDefined(const std::string& token) const
{
	for ( StringList::const_iterator it = mDefines.begin(); it != mDefines.end(); ++it ) {
		if ( (*it) == token ) {
			return true;
		}
	}

	return false;
}

bool Tokenizer::isDigit(const std::string& token) const
{
	if ( token.empty() ) {
		return false;
	}

	int numOfDots = 0;

	for ( unsigned int c = 0; c < token.size(); c++ ) {
		switch ( token[c] ) {
			case '.':
				numOfDots++;
				if ( numOfDots > 1 ) {
					return false;
				}
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '0':
				break;
			default:
				return false;
		}
	}

	return true;
}

bool Tokenizer::isIdentifer(const std::string& token) const
{
	for ( StringList::const_iterator it = mIdentifiers.begin(); it != mIdentifiers.end(); ++it ) {
		if ( (*it) == token ) {
			return true;
		}
	}

	return false;
}

bool Tokenizer::isKeyword(const std::string& token) const
{
	for ( StringList::const_iterator it = mKeywords.begin(); it != mKeywords.end(); ++it ) {
		if ( (*it) == token ) {
			return true;
		}
	}

	return false;
}

bool Tokenizer::isLanguageFeature(const std::string& content) const
{
	if ( content == "deprecated" ) return true;
	if ( content == "notimplemented" ) return true;
	if ( content == "stable" ) return true;
	if ( content == "unstable" ) return true;

	return false;
}

bool Tokenizer::isLiteral(const std::string& token) const
{
	if ( token.size() > 1 ) {
		// double quotated literals
		if ( (token.at(0) == '"' && token.at(token.size() - 1) == '"')) {
			return true;
		}
		// single quotated literals
		if ( (token.at(0) == '\'' && token.at(token.size() - 1) == '\'') ) {
			return true;
		}
	}

	return false;
}

bool Tokenizer::isPrototype(TokenIterator token) const
{
	if ( token->type() != Token::Type::IDENTIFER ) {
		return false;
	}
	token++;

	if ( token->type() != Token::Type::RESERVED && token->content() != "of" ) {
		return false;
	}
	token++;

	if ( token->type() != Token::Type::IDENTIFER ) {
		return false;
	}

	return true;
}

bool Tokenizer::isReservedWord(const std::string& token) const
{
	for ( StringList::const_iterator it = mReservedWords.begin(); it != mReservedWords.end(); ++it ) {
		if ( (*it) == token ) {
			return true;
		}
	}

	return false;
}

bool Tokenizer::isType(const std::string& token) const
{
	for ( StringList::const_iterator it = mTypes.begin(); it != mTypes.end(); ++it ) {
		if ( (*it) == token ) {
			return true;
		}
	}

	return false;
}

bool Tokenizer::isVisibility(const std::string& token) const
{
	if ( token == "private" || token == "protected" || token == "public" ) {
		return true;
	}

	return false;
}

bool Tokenizer::isWhiteSpace(const std::string& token) const
{
	return (WHITESPACES.find_first_of(token) != std::string::npos);
}

void Tokenizer::process()
{
	size_t offset = 0;
	std::string token;

	bool isMultiLineComment = false;
	bool isPreprocessorDirective = false;
	bool isSingleLineComment = false;
	bool isString = false;

	char lastChar = 0;
	Utils::Position pos(1, 1);

	while ( offset < mContent.size() ) {
		char thisChar = mContent[offset++];
		size_t i = DELIMITERS.find_first_of(thisChar);

		// preprocessor directives as single line comments '#'
		if ( !isMultiLineComment && !isSingleLineComment && !isString && thisChar == '#' ) {
			isPreprocessorDirective = true;
		}
		// single line comments '//'
		if ( !isMultiLineComment && !isSingleLineComment && !isString && lastChar == '/' && thisChar == '/' ) {
			isSingleLineComment = true;
			// remove last inserted token
			mTokens.pop_back();
		}
		// multiline comments '/*'
		if ( !isMultiLineComment && !isSingleLineComment && !isString && lastChar == '/' && thisChar == '*' ) {
			isMultiLineComment = true;
			// remove last inserted token
			mTokens.pop_back();
		}

		if ( isPreprocessorDirective ) {
			// not in use atm so just ignore it
		}
		// don't parse comments
		else if ( !isMultiLineComment && !isSingleLineComment ) {
			// are we reading a string?
			if ( (thisChar == '\"' /* || thisChar == '\''*/) && lastChar != '\\' ) {
				isString = !isString;
			}

			if ( !isString && i != std::string::npos ) {
				if ( !token.empty() ) {
					if ( thisChar == '"' /*|| thisChar == '\''*/ ) {
						token += thisChar;
						thisChar = 0;
					}
					addToken(createToken(token, pos));
				}

				token.clear();
				token = thisChar;

				if ( !token.empty() && token.at(0) != 0 ) {
					addToken(createToken(token, pos));
				}

				token.clear();
			}
			else {
				// only add char if it is no '\'
				if ( thisChar != '\\' ) {
					token += thisChar;
				}
			}
		}

		// multiline comments '*/'
		if ( isMultiLineComment && lastChar == '*' && thisChar == '/' ) {
			isMultiLineComment = false;
		}

		// counting lines and columns
		pos.column++;
		if ( thisChar == '\n' ) {
			isPreprocessorDirective = false;
			isSingleLineComment = false;
			pos.line++;
			pos.column = 1;
		}

		// keep track of our last char (i.e. for escape sequences)
		lastChar = thisChar;
	}

	// add end of file token
	addToken(Token(Token::Type::ENDOFFILE));

	removeWhiteSpaces();		// remove all whitespaces
	replaceAssignments();
	replacePrototypes();
	//classify();
}

void Tokenizer::removeWhiteSpaces()
{
	TokenList tmp;

	for ( TokenList::iterator it = mTokens.begin(); it != mTokens.end(); ++it ) {
		if ( (*it).type() != Token::Type::WHITESPACE ) {
			tmp.push_back((*it));
		}
	}

	mTokens = tmp;
}

void Tokenizer::replaceAssignments()
{
	TokenList tmp;
	Token::Type::E lastType = Token::Type::UNKNOWN;
	TokenIterator token = mTokens.begin();

	// try to combine all compare tokens
	while ( token != mTokens.end() ) {
		bool changed = false;
		Token::Type::E activeType = token->type();

		if ( activeType == Token::Type::EQUAL ) {
			if ( lastType == Token::Type::EQUAL ) {
				// ==
				changed = true;
				// remove last added token ...
				tmp.pop_back();
				// ... and add COMPARE_EQUAL instead
				tmp.push_back(Token(Token::Type::COMPARE_EQUAL, "=="));
			}
			else if ( lastType == Token::Type::GREATER ) {
				// >=
				changed = true;
				// remove last added token ...
				tmp.pop_back();
				// ... and add COMPARE_GREATER_EQUAL instead
				tmp.push_back(Token(Token::Type::COMPARE_GREATER_EQUAL, ">="));
			}
			else if ( lastType == Token::Type::LESS ) {
				// <=
				changed = true;
				// remove last added token ...
				tmp.pop_back();
				// ... and add COMPARE_LESS_EQUAL instead
				tmp.push_back(Token(Token::Type::COMPARE_LESS_EQUAL, "<="));
			}
			else if ( lastType == Token::Type::MATH_ADD ) {
				// +=
				changed = true;
				// remove last added token ...
				tmp.pop_back();
				// ... and add ASSIGN_ADD instead
				tmp.push_back(Token(Token::Type::ASSIGN_ADD, "+="));
			}
			else if ( lastType == Token::Type::MATH_DIV ) {
				// /=
				changed = true;
				// remove last added token ...
				tmp.pop_back();
				// ... and add ASSIGN_DIVIDE instead
				tmp.push_back(Token(Token::Type::ASSIGN_DIVIDE, "/="));
			}
			else if ( lastType == Token::Type::MATH_MULTI ) {
				// *=
				changed = true;
				// remove last added token ...
				tmp.pop_back();
				// ... and add ASSIGN_MULTI instead
				tmp.push_back(Token(Token::Type::ASSIGN_MULTI, "*="));
			}
			else if ( lastType == Token::Type::MATH_SUBTRACT ) {
				// -=
				changed = true;
				// remove last added token ...
				tmp.pop_back();
				// ... and add ASSIGN_SUBTRACT instead
				tmp.push_back(Token(Token::Type::ASSIGN_SUBTRACT, "-="));
			}
		}

		lastType = token->type();
		if ( !changed ) {
			tmp.push_back((*token));
		}

		token++;
	}

	mTokens = tmp;
	tmp.clear();

	for ( TokenIterator it = mTokens.begin(); it != mTokens.end(); ++it ) {
		if ( (*it).type() == Token::Type::EQUAL ) {
			tmp.push_back(Token(Token::Type::ASSIGN, (*it).content(), (*it).position()));
		}
		else {
			tmp.push_back((*it));
		}
	}

	mTokens = tmp;
}

/*
 *  This removes all 'of' tokens that are part of a prototype instantiation
 *  and changes the token type of the prototype from identifier to prototype.
 */
void Tokenizer::replacePrototypes()
{
	TokenList::iterator token = mTokens.begin();

	// try to combine all prototype tokens
	while ( token != mTokens.end() ) {
		// find prototype as ( identifier reserved identifier )
		if ( isPrototype(token) ) {
			// reset it's type
			(*token).resetTypeTo(Token::Type::PROTOTYPE);

			// and remove the following 'of'-token
			token++;
			mTokens.erase(token++);
			continue;

/*
			// and remove the following 2 tokens ('of' & type)
			token++;
			mTokens.erase(token++);
			mTokens.erase(token++);
			continue;
*/
		}

		token++;
	}
}

const TokenList& Tokenizer::tokens() const
{
	return mTokens;
}


}
