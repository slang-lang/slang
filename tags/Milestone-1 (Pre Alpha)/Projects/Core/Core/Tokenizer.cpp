
// Header
#include "Tokenizer.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Keywords/for.h>
#include <Core/Keywords/if.h>
#include <Core/Keywords/print.h>
#include <Core/Keywords/return.h>
#include <Core/Utils/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {


const std::string CONTROLCHARS	= "#,;:=()[]{}<>+-*/%&|'\" ";
const std::string DELIMITERS	= "#,;:=()[]{}<>+-*/%&|'\"\t\n\r ";
const std::string WHITESPACES	= "\t\n\r ";


Tokenizer::Tokenizer(const std::string& filename, const std::string& content)
: mContent(content),
  mFilename(filename)
{
	mLanguageFeatures = provideLanguageFeatures();
	mKeywords = provideKeyWords();
	mModifiers = provideModifiers();
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
				throw Utils::Exceptions::SyntaxError("'(' expected but '" + (*token).content() + "' found", token->position());
			}

		}
		else if ( (*token).content() == "if" ) {
			// if the next token is no '(' throw a synthax error exception
			if ( (*++token).type() != Token::Type::PARENTHESIS_OPEN ) {
				throw Utils::Exceptions::SyntaxError("'(' expected but '" + (*token).content() + "' found", token->position());
			}

		}
		else if ( (*token).content() == "print" ) {
			// if the next token is no '(' throw a synthax error exception
			if ( (*++token).type() != Token::Type::PARENTHESIS_OPEN ) {
				throw Utils::Exceptions::SyntaxError("'(' expected but '" + (*token).content() + "' found", token->position());
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
				throw Utils::Exceptions::SyntaxError("';' expected but '" + (*token).content() + "' found", token->position());
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
				throw Utils::Exceptions::SyntaxError("';' expected but '" + (*token).content() + "' found", token->position());
			}

			Keywords::Return r;
			r.tokens(list);

			keywords.push_back(r);
		}

		token++;
	}



}

Token Tokenizer::createToken(const std::string& con, const Utils::Position& position)
{
	std::string content = con;

	Token::Category::E category = Token::Category::None;
	Token::Type::E type = Token::Type::IDENTIFER;

	if ( content == "=" ) { category = Token::Category::Assignment; type = Token::Type::ASSIGN; }
	else if ( content == "&" ) { category = Token::Category::Operator; type = Token::Type::BITAND; }
	else if ( content == "|" ) { category = Token::Category::Operator; type = Token::Type::BITOR; }
	else if ( content == "," ) { type = Token::Type::COLON; }
	else if ( content == "." ) { type = Token::Type::DOT; }
	else if ( content == ";" ) { type = Token::Type::SEMICOLON; }
	else if ( content == "'" ) { type = Token::Type::QUOTATION_SINGLE; }
	else if ( content == "\"" ) { type = Token::Type::QUOTATION_DOUBLE; }
	else if ( content == "[" ) { type = Token::Type::BRACKET_OPEN; }
	else if ( content == "]" ) { type = Token::Type::BRACKET_CLOSE; }
	else if ( content == "{" ) { type = Token::Type::BRACKET_CURLY_OPEN; }
	else if ( content == "}" ) { type = Token::Type::BRACKET_CURLY_CLOSE; }
	else if ( content == ">" ) { category = Token::Category::Operator; type = Token::Type::COMPARE_GREATER; }
	else if ( content == "<" ) { category = Token::Category::Operator; type = Token::Type::COMPARE_LESS; }
	else if ( content == "(" ) { type = Token::Type::PARENTHESIS_OPEN; }
	else if ( content == ")" ) { type = Token::Type::PARENTHESIS_CLOSE; }
	else if ( content == "+" ) { category = Token::Category::Operator; type = Token::Type::MATH_ADD; }
	else if ( content == "/" ) { category = Token::Category::Operator; type = Token::Type::MATH_DIVIDE; }
	else if ( content == "%" ) { category = Token::Category::Operator; type = Token::Type::MATH_MODULO; }
	else if ( content == "*" ) { category = Token::Category::Operator; type = Token::Type::MATH_MULTIPLY; }
	else if ( content == "-" ) { category = Token::Category::Operator; type = Token::Type::MATH_SUBTRACT; }
	else if ( isBoolean(content) ) { category = Token::Category::Constant; type = Token::Type::CONST_BOOLEAN; }
	else if ( isFloat(content) ) { category = Token::Category::Constant; type = Token::Type::CONST_FLOAT; }
	else if ( isIdentifer(content) ) { type = Token::Type::IDENTIFER; }
	else if ( isInteger(content) ) { category = Token::Category::Constant; type = Token::Type::CONST_INTEGER; }
	else if ( isKeyword(content) ) { type = Token::Type::KEYWORD; }
	else if ( isLanguageFeature(content) ) { type = Token::Type::LANGUAGEFEATURE; }
	else if ( isLiteral(content) ) { category = Token::Category::Constant; type = Token::Type::CONST_LITERAL;
		// remove leading and trailing (", ') quotation marks (", ')
		content = con.substr(1, con.length() - 2);
	}
	else if ( isModifier(content) ) { category = Token::Category::Modifier; type = Token::Type::LANGUAGEFEATURE; }
	else if ( isNumber(content) ) { category = Token::Category::Constant; type = Token::Type::CONST_NUMBER; }
	else if ( isReservedWord(content) ) { type = Token::Type::RESERVED; }
	else if ( isType(content) ) { type = Token::Type::TYPE; }
	else if ( isVisibility(content) ) { type = Token::Type::VISIBILITY; }
	else if ( isWhiteSpace(content) ) { type = Token::Type::WHITESPACE; }

	Token token(category, type, content, position);
	token.setOptional(type == Token::Type::LANGUAGEFEATURE);
	return token;
}

bool Tokenizer::isBoolean(const std::string& token) const
{
	return ( token == FALSE || token == TRUE );
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

bool Tokenizer::isFloat(const std::string& token) const
{
	if ( token.empty() ) {
		return false;
	}

	int numOfDots = 0;

	for ( unsigned int c = 0; c < token.size() - 1; c++ ) {
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

	// the last char of our token has to be an 'f'
	if ( token[token.size() - 1] == 'f' && token.size() > 1 ) {
		return true;
	}

	return false;
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

bool Tokenizer::isInteger(const std::string& token) const
{
	if ( token.empty() ) {
		return false;
	}

	for ( unsigned int c = 0; c < token.size() - 1; c++ ) {
		switch ( token[c] ) {
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

	// the last char of our token has to be an 'i'
	if ( token[token.size() - 1] == 'i' && token.size() > 1 ) {
		return true;
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

bool Tokenizer::isLanguageFeature(const std::string& token) const
{
	for ( StringList::const_iterator it = mLanguageFeatures.begin(); it != mLanguageFeatures.end(); ++it ) {
		if ( (*it) == token ) {
			return true;
		}
	}

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

bool Tokenizer::isModifier(const std::string& token) const
{
	for ( StringList::const_iterator it = mModifiers.begin(); it != mModifiers.end(); ++it ) {
		if ( (*it) == token ) {
			return true;
		}
	}

	return false;
}

bool Tokenizer::isNumber(const std::string& token) const
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
	if ( token == PRIVATE || token == PROTECTED || token == PUBLIC ) {
		return true;
	}

	return false;
}

bool Tokenizer::isWhiteSpace(const std::string& token) const
{
	return (WHITESPACES.find_first_of(token) != std::string::npos);
}

/*
 * This merges all pairs of & or | operators together (i.e. '&' '&' becomes '&&')
 */
void Tokenizer::mergeBooleanOperators()
{
	TokenList tmp;
	Token::Type::E lastType = Token::Type::UNKNOWN;
	TokenIterator token = mTokens.begin();

	// try to combine all compare tokens
	while ( token != mTokens.end() ) {
		bool changed = false;
		Token::Type::E activeType = token->type();

		if ( (lastType == Token::Type::BITAND) && (activeType == Token::Type::BITAND) ) {
			// ==
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add AND instead
			tmp.push_back(Token(Token::Category::Operator, Token::Type::AND, "&&", token->position()));
		}
		else if ( (lastType == Token::Type::BITOR) && (activeType == Token::Type::BITOR) ) {
			// >=
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add OR instead
			tmp.push_back(Token(Token::Category::Operator, Token::Type::OR, "||", token->position()));
		}

		lastType = token->type();
		if ( !changed ) {
			tmp.push_back((*token));
		}

		token++;
	}

	mTokens = tmp;
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
	Utils::Position pos(mFilename, 1, 1);

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
	replaceAssignments();		// replace assignment tokens with compare tokens (if present)
	mergeBooleanOperators();	// merge '&' '&' into '&&'
	replaceOperators();			// combine 'operator' identifiers with the next following token i.e. 'operator' '+' => 'operator+'
	replacePrototypes();		//
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

/*
 * replaceAssignments replaces/merges all assignment tokens with compare tokens (if present), i.e. '+' '=' => '+='
 */
void Tokenizer::replaceAssignments()
{
	TokenList tmp;
	Token::Type::E lastType = Token::Type::UNKNOWN;
	TokenIterator token = mTokens.begin();

	// try to combine all compare tokens
	while ( token != mTokens.end() ) {
		bool changed = false;
		Token::Type::E activeType = token->type();

		if ( (lastType == Token::Type::ASSIGN) && (activeType == Token::Type::ASSIGN) ) {
			// ==
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add COMPARE_EQUAL instead
			tmp.push_back(Token(Token::Category::Assignment, Token::Type::COMPARE_EQUAL, "==", token->position()));
		}
		else if ( (lastType == Token::Type::GREATER || lastType == Token::Type::COMPARE_GREATER) && (activeType == Token::Type::ASSIGN) ) {
			// >=
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add COMPARE_GREATER_EQUAL instead
			tmp.push_back(Token(Token::Category::Assignment, Token::Type::COMPARE_GREATER_EQUAL, ">=", token->position()));
		}
		else if ( (lastType == Token::Type::LESS || lastType == Token::Type::COMPARE_LESS) && (activeType == Token::Type::ASSIGN) ) {
			// <=
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add COMPARE_LESS_EQUAL instead
			tmp.push_back(Token(Token::Category::Assignment, Token::Type::COMPARE_LESS_EQUAL, "<=", token->position()));
		}
		else if ( (lastType == Token::Type::MATH_ADD) && (activeType == Token::Type::ASSIGN) ) {
			// +=
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add ASSIGN_ADD instead
			tmp.push_back(Token(Token::Category::Assignment, Token::Type::ASSIGN_ADD, "+=", token->position()));
		}
		else if ( (lastType == Token::Type::MATH_DIVIDE) && (activeType == Token::Type::ASSIGN) ) {
			// /=
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add ASSIGN_DIVIDE instead
			tmp.push_back(Token(Token::Category::Assignment, Token::Type::ASSIGN_DIVIDE, "/=", token->position()));
		}
		else if ( (lastType == Token::Type::MATH_MODULO) && (activeType == Token::Type::ASSIGN) ) {
			// %=
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add ASSIGN_MULTI instead
			tmp.push_back(Token(Token::Category::Assignment, Token::Type::ASSIGN_MODULO, "*=", token->position()));
		}
		else if ( (lastType == Token::Type::MATH_MULTIPLY) && (activeType == Token::Type::ASSIGN) ) {
			// *=
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add ASSIGN_MULTI instead
			tmp.push_back(Token(Token::Category::Assignment, Token::Type::ASSIGN_MULTIPLY, "*=", token->position()));
		}
		else if ( (lastType == Token::Type::MATH_SUBTRACT) && (activeType == Token::Type::ASSIGN) ) {
			// -=
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add ASSIGN_SUBTRACT instead
			tmp.push_back(Token(Token::Category::Assignment, Token::Type::ASSIGN_SUBTRACT, "-=", token->position()));
		}

		lastType = token->type();
		if ( !changed ) {
			tmp.push_back((*token));
		}

		token++;
	}

	mTokens = tmp;
}

/*
 * This merges all 'operator' tokens with their according operator (+, -, *, /, &, |, =, ==, <, <=, >, >=, etc.)
 */
void Tokenizer::replaceOperators()
{
	TokenList::iterator token = mTokens.begin();

	// try to combine all operator tokens
	while ( token != mTokens.end() ) {
		if ( (*token).type() == Token::Type::RESERVED && (*token).content() == RESERVED_WORD_OPERATOR ) {
			// we found an operator
			TokenList::iterator opToken = token;

			// remove the following 'operator'-token
			token++;

			// and reset our opToken's type
			(*opToken).resetTypeTo(Token::Type::IDENTIFER);
			(*opToken).resetContentTo(RESERVED_WORD_OPERATOR + (*token).content());

			mTokens.erase(token++);
			continue;
		}

		token++;
	}
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