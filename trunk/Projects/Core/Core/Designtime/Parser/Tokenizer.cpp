
// Header
#include "Tokenizer.h"

// Library includes

// Project includes
#include <Core/Consts.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


const std::string CONTROLCHARS	= "#.,;:=()[]{}!<>+-*/%&|~'\" ";
const std::string WHITESPACES	= "\t\n\r ";
const std::string DELIMITERS	= CONTROLCHARS + WHITESPACES;


Tokenizer::Tokenizer(const std::string& filename, const std::string& content)
: mContent(content),
  mFilename(filename)
{
	mLanguageFeatures = provideLanguageFeatures();
	mKeywords = provideKeyWords();
	mModifiers = provideModifiers();
	mReservedWords = provideReservedWords();
	mTypes = provideAtomicTypes();
}

void Tokenizer::addToken(const std::string &con, const Common::Position &position)
{
	std::string content = con;

	Token::Category::E category = Token::Category::None;
	Token::Type::E type = Token::Type::IDENTIFER;

	if ( content == "=" ) { category = Token::Category::Assignment; type = Token::Type::ASSIGN; }
	else if ( content == "&" ) { category = Token::Category::Operator; type = Token::Type::BITAND; }
	else if ( content == "|" ) { category = Token::Category::Operator; type = Token::Type::BITOR; }
	else if ( content == "," ) { type = Token::Type::COMMA; }
	else if ( content == "." ) { type = Token::Type::SCOPE; }
	else if ( content == ";" ) { type = Token::Type::SEMICOLON; }
	else if ( content == ":" ) { type = Token::Type::COLON; }
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
	else if ( content == "+" ) { category = Token::Category::Operator; type = Token::Type::MATH_ADDITION; }
	else if ( content == "/" ) { category = Token::Category::Operator; type = Token::Type::MATH_DIVIDE; }
	else if ( content == "%" ) { category = Token::Category::Operator; type = Token::Type::MATH_MODULO; }
	else if ( content == "*" ) { category = Token::Category::Operator; type = Token::Type::MATH_MULTIPLY; }
	else if ( content == "-" ) { category = Token::Category::Operator; type = Token::Type::MATH_SUBTRACT; }
	else if ( content == OPERATOR_IS ) { category = Token::Category::Operator; type = Token::Type::OPERATOR_IS; }
	else if ( content == "!" ) { category = Token::Category::Operator; type = Token::Type::OPERATOR_NOT; }
	else if ( content == "~" ) { category = Token::Category::Operator; type = Token::Type::TILDE; }
	else if ( isBoolean(content) ) { category = Token::Category::Constant; type = Token::Type::CONST_BOOLEAN; }
	else if ( isDouble(content) ) { category = Token::Category::Constant; type = Token::Type::CONST_DOUBLE;
		// remove trailing 'd' character
		content = con.substr(0, con.length() - 1);
	}
	else if ( isFloat(content) ) { category = Token::Category::Constant; type = Token::Type::CONST_FLOAT;
		// remove trailing 'f' character
		content = con.substr(0, con.length() - 1);
	}
	else if ( isInteger(content) ) { category = Token::Category::Constant; type = Token::Type::CONST_INTEGER; }
	else if ( isIntegerWithType(content) ) { category = Token::Category::Constant; type = Token::Type::CONST_INTEGER;
		// remove trailing 'i' character
		content = con.substr(0, con.length() - 1);
	}
	else if ( isKeyword(content) ) { category = Token::Category::Keyword; type = Token::Type::KEYWORD; }
	else if ( isLanguageFeature(content) ) { category = Token::Category::Modifier; type = Token::Type::LANGUAGEFEATURE; }
	else if ( isLiteral(content) ) { category = Token::Category::Constant; type = Token::Type::CONST_LITERAL;
		// remove leading and trailing (", ') quotation marks (", ')
		content = con.substr(1, con.length() - 2);
	}
	else if ( isModifier(content) ) { category = Token::Category::Modifier; type = Token::Type::MODIFIER; }
	else if ( isReservedWord(content) ) { category = Token::Category::ReservedWord; type = Token::Type::RESERVED_WORD; }
	else if ( isType(content) ) { category = Token::Category::Identifier; type = Token::Type::TYPE; }
	else if ( isVisibility(content) ) { type = Token::Type::VISIBILITY; }
	else if ( isWhiteSpace(content) ) { category = Token::Category::Ignorable; type = Token::Type::WHITESPACE; }

	Token token(category, type, content, position);
	token.setOptional(category == Token::Category::Modifier || type == Token::Type::LANGUAGEFEATURE);

	mTokens.push_back(token);
}

void Tokenizer::addToken(const Token& token)
{
	if ( token.content().empty() && token.type() == Token::Type::UNKNOWN ) {
		// ignore this non-existing token
		return;
	}

	// only add valid tokens to our token list
	mTokens.push_back(token);
}

bool Tokenizer::isBoolean(const std::string& token) const
{
	return ( token == BOOL_FALSE || token == BOOL_TRUE );
}

bool Tokenizer::isDouble(const std::string& token) const
{
	if ( token.size() <= 1 ) {
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

	// the last char of our token has to be an 'd'
	return token[token.size() - 1] == 'd';
}

bool Tokenizer::isFloat(const std::string& token) const
{
	if ( token.size() <= 1 ) {
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

	// the last char of our token has to be an 'f'
	return token[token.size() - 1] == 'f';
}

bool Tokenizer::isInteger(const std::string& token) const
{
	if ( token.empty() ) {
		return false;
	}

	for ( unsigned int c = 0; c < token.size(); c++ ) {
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

	return true;
}

bool Tokenizer::isIntegerWithType(const std::string& token) const
{
	if ( token.size() <= 1 ) {
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
	return token[token.size() - 1] == 'i';
}

bool Tokenizer::isKeyword(const std::string& token) const
{
	return mKeywords.find(token) != mKeywords.end();
}

bool Tokenizer::isLanguageFeature(const std::string& token) const
{
	return mLanguageFeatures.find(token) != mLanguageFeatures.end();
}

bool Tokenizer::isLiteral(const std::string& token) const
{
	if ( token.size() > 1 ) {
		// double quoted literals
		if ( (token.at(0) == '"' && token.at(token.size() - 1) == '"')) {
			return true;
		}
		// single quoted literals
		if ( (token.at(0) == '\'' && token.at(token.size() - 1) == '\'') ) {
			return true;
		}
	}

	return false;
}

bool Tokenizer::isModifier(const std::string& token) const
{
	return mModifiers.find(token) != mModifiers.end();
}

bool Tokenizer::isReservedWord(const std::string& token) const
{
	return mReservedWords.find(token) != mReservedWords.end();
}

bool Tokenizer::isType(const std::string& token) const
{
	return mTypes.find(token) != mTypes.end();
}

bool Tokenizer::isVisibility(const std::string& token) const
{
	return token == PRIVATE || token == PROTECTED || token == PUBLIC;
}

bool Tokenizer::isWhiteSpace(const std::string& token) const
{
	return (WHITESPACES.find_first_of(token) != std::string::npos);
}

/*
 * mergeBooleanOperators: merges all pairs of & or | operators together (i.e. '&' '&' become '&&')
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
			// && and
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add AND instead
			tmp.push_back(Token(Token::Category::Operator, Token::Type::AND, "&&", token->position()));
		}
		else if ( (lastType == Token::Type::BITOR) && (activeType == Token::Type::BITOR) ) {
			// || or
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add OR instead
			tmp.push_back(Token(Token::Category::Operator, Token::Type::OR, "||", token->position()));
		}
		else if ( (lastType == Token::Type::OPERATOR_NOT) && (activeType == Token::Type::BITAND) ) {
			// !& negative and
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add OR instead
			tmp.push_back(Token(Token::Category::Operator, Token::Type::NAND, "!&", token->position()));
		}
		else if ( (lastType == Token::Type::OPERATOR_NOT) && (activeType == Token::Type::BITOR) ) {
			// !| negative or
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add OR instead
			tmp.push_back(Token(Token::Category::Operator, Token::Type::NOR, "!|", token->position()));
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
 * mergeOtherOperators: merges '[' ']' operators into '[]'
 */
void Tokenizer::mergeOtherOperators()
{
	TokenList tmp;
	Token::Type::E lastType = Token::Type::UNKNOWN;
	TokenIterator token = mTokens.begin();

	// try to combine all other operator tokens
	while ( token != mTokens.end() ) {
		bool changed = false;
		Token::Type::E activeType = token->type();

		if ( (lastType == Token::Type::BRACKET_OPEN) && (activeType == Token::Type::BRACKET_CLOSE) ) {
			// && and
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add AND instead
			tmp.push_back(Token(Token::Category::Operator, Token::Type::ARRAY_SUBSCRIPT, "[]", token->position()));
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
 * mergeInfixPostfixOperators: merges all pairs of + or - operators together (i.e. '+' '+' become '++')
 */
void Tokenizer::mergeInfixPostfixOperators()
{
	TokenList tmp;
	Token::Type::E lastType = Token::Type::UNKNOWN;
	TokenIterator token = mTokens.begin();

	// try to combine all compare tokens
	while ( token != mTokens.end() ) {
		bool changed = false;
		Token::Type::E activeType = token->type();

		if ( (lastType == Token::Type::MATH_SUBTRACT) && (activeType == Token::Type::MATH_SUBTRACT) ) {
			// --
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add OR instead
			tmp.push_back(Token(Token::Category::Operator, Token::Type::OPERATOR_DECREMENT, "--", token->position()));
		}
		else if ( (lastType == Token::Type::MATH_ADDITION) && (activeType == Token::Type::MATH_ADDITION) ) {
			// ++
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add AND instead
			tmp.push_back(Token(Token::Category::Operator, Token::Type::OPERATOR_INCREMENT, "++", token->position()));
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
	size_t size = mContent.size();
	std::string token;

	bool isMultiLineComment = false;
	bool isPreprocessorDirective = false;
	bool isSingleLineComment = false;
	bool isString = false;

	char lastChar = 0;
	Common::Position pos(mFilename, 1, 1);

	while ( offset < size ) {
		char thisChar = mContent[offset++];
		//size_t i = DELIMITERS.find_first_of(thisChar);

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

			if ( !isString && DELIMITERS.find_first_of(thisChar) != std::string::npos ) {
				if ( !token.empty() ) {
					if ( thisChar == '"' /*|| thisChar == '\''*/ ) {
						token += thisChar;
						thisChar = 0;
					}
					addToken(token, pos);
				}

				token.clear();
				token = thisChar;

				if ( !token.empty() && token.at(0) != 0 ) {
					addToken(token, pos);
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
		pos.mColumn++;
		if ( thisChar == '\n' ) {
			isPreprocessorDirective = false;
			isSingleLineComment = false;
			pos.mLine++;
			pos.mColumn = 1;

			thisChar = 0;
		}

		// keep track of our last char (i.e. for escape sequences)
		lastChar = thisChar;
	}

	if ( lastChar != 0 ) {
		addToken(token, pos);
	}

	addToken(Token(Token::Type::ENDOFFILE));	// add end of file token

	removeWhiteSpaces();			// remove all white spaces
	replaceAssignments();			// replace assignment tokens with compare tokens (if present)
	mergeBooleanOperators();		// merge '&' '&' into '&&'
	mergeInfixPostfixOperators();	// merge '+' '+' into '++'
	mergeOtherOperators();			// merge '[' ']' into '[]'
	replaceConstDataTypes();		// combines CONST_INTEGER '.' CONST_INTEGER <data type> into a CONST_FLOAT or CONST_DOUBLE
	replaceOperators();				// combine 'operator' identifiers with the next following token i.e. 'operator' '+' => 'operator+'
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
 * replaceAssignments replaces/merges all assignment tokens with compare tokens (if present), i.e. '+' & '=' => '+='
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
			tmp.push_back(Token(Token::Category::Comparator, Token::Type::COMPARE_EQUAL, "==", token->position()));
		}
		else if ( (lastType == Token::Type::BITAND) && (activeType == Token::Type::ASSIGN) ) {
			// &=
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add ASSIGN_ADD instead
			tmp.push_back(Token(Token::Category::Assignment, Token::Type::ASSIGN_BITAND, "&=", token->position()));
		}
		else if ( (lastType == Token::Type::BITCOMPLEMENT) && (activeType == Token::Type::ASSIGN) ) {
			// ~=
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add ASSIGN_ADD instead
			tmp.push_back(Token(Token::Category::Assignment, Token::Type::ASSIGN_BITCOMPLEMENT, "~=", token->position()));
		}
		else if ( (lastType == Token::Type::BITOR) && (activeType == Token::Type::ASSIGN) ) {
			// |=
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add ASSIGN_ADD instead
			tmp.push_back(Token(Token::Category::Assignment, Token::Type::ASSIGN_BITOR, "|=", token->position()));
		}
		else if ( (lastType == Token::Type::OPERATOR_NOT) && (activeType == Token::Type::ASSIGN) ) {
			// !=
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add ASSIGN_ADD instead
			tmp.push_back(Token(Token::Category::Comparator, Token::Type::COMPARE_UNEQUAL, "!=", token->position()));
		}
		else if ( (lastType == Token::Type::GREATER || lastType == Token::Type::COMPARE_GREATER) && (activeType == Token::Type::ASSIGN) ) {
			// >=
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add COMPARE_GREATER_EQUAL instead
			tmp.push_back(Token(Token::Category::Comparator, Token::Type::COMPARE_GREATER_EQUAL, ">=", token->position()));
		}
		else if ( (lastType == Token::Type::LESS || lastType == Token::Type::COMPARE_LESS) && (activeType == Token::Type::ASSIGN) ) {
			// <=
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add COMPARE_LESS_EQUAL instead
			tmp.push_back(Token(Token::Category::Comparator, Token::Type::COMPARE_LESS_EQUAL, "<=", token->position()));
		}
		else if ( (lastType == Token::Type::MATH_ADDITION) && (activeType == Token::Type::ASSIGN) ) {
			// +=
			changed = true;
			// remove last added token ...
			tmp.pop_back();
			// ... and add ASSIGN_ADD instead
			tmp.push_back(Token(Token::Category::Assignment, Token::Type::ASSIGN_ADDITION, "+=", token->position()));
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
 * This merges all integer consts with their following data type (also looks at the scope token to produce doubles and floats i.e. 17.3f)
 * CONST_INTEGER 'f': 17 'f'
 * CONST_INTEGER '.' 'f': 17 '.' 'f'
 * CONST_INTEGER '.' CONST_INTEGER 'f': 17 '.' 3 'f'
 */
void Tokenizer::replaceConstDataTypes()
{
	TokenList::iterator token = mTokens.begin();
	TokenList::iterator tmp;

	// try to combine all operator tokens
	while ( token != mTokens.end() ) {
		// all our consts start with a CONST_INTEGER token
		if ( token->type() == Token::Type::CONST_INTEGER ) {
			int numCombines = 0;

			tmp = lookahead(token, numCombines + 1);

			if ( tmp->type() == Token::Type::SCOPE ) {
				// CONST_INTEGER '.'
				numCombines++;

				tmp = lookahead(token, numCombines + 1);

				if ( tmp->type() == Token::Type::CONST_INTEGER ) {
					// CONST_INTEGER '.' CONST_INTEGER
					numCombines++;

					tmp = lookahead(token, numCombines + 1);

					if ( tmp->type() == Token::Type::IDENTIFER ) {
						if ( tmp->content() == "d" ) {
							// CONST_INTEGER '.' CONST_INTEGER 'd'
							numCombines++;
							tmp->resetContentTo("");
							tmp->resetTypeTo(Token::Type::CONST_DOUBLE);
						}
						else if ( tmp->content() == "f" ) {
							// CONST_INTEGER '.' CONST_INTEGER 'f'
							numCombines++;
							tmp->resetContentTo("");
							tmp->resetTypeTo(Token::Type::CONST_FLOAT);
						}
					}
					else if ( tmp->type() == Token::Type::CONST_DOUBLE ) {
						// CONST_DOUBLE 'd'
						numCombines++;
					}
					else if ( tmp->type() == Token::Type::CONST_FLOAT ) {
						// CONST_FLOAT 'f'
						numCombines++;
					}
					else if ( tmp->type() == Token::Type::CONST_INTEGER ) {
						// CONST_INTEGER 'i'
						numCombines++;
					}
				}
				else if ( tmp->type() == Token::Type::IDENTIFER ) {
					if ( tmp->content() == "d" ) {
						// CONST_INTEGER '.' 'd'
						numCombines++;
						tmp->resetContentTo("");
						tmp->resetTypeTo(Token::Type::CONST_DOUBLE);
					}
					else if ( tmp->content() == "f" ) {
						// CONST_INTEGER '.' 'f'
						numCombines++;
						tmp->resetContentTo("");
						tmp->resetTypeTo(Token::Type::CONST_FLOAT);
					}
				}
				else if ( tmp->type() == Token::Type::CONST_DOUBLE ) {
					// CONST_DOUBLE 'd'
					numCombines++;
				}
				else if ( tmp->type() == Token::Type::CONST_FLOAT ) {
					// CONST_FLOAT 'f'
					numCombines++;
				}
			}
			else if ( tmp->type() == Token::Type::IDENTIFER ) {
				if ( tmp->content() == "d" ) {
					// CONST_INTEGER 'd'
					numCombines++;
					tmp->resetContentTo("");
					tmp->resetTypeTo(Token::Type::CONST_DOUBLE);
				}
				else if ( tmp->content() == "f" ) {
					// CONST_INTEGER 'f'
					numCombines++;
					tmp->resetContentTo("");
					tmp->resetTypeTo(Token::Type::CONST_FLOAT);
				}
				else if ( tmp->content() == "i" ) {
					// CONST_INTEGER 'i'
					numCombines++;
					tmp->resetContentTo("");
					tmp->resetTypeTo(Token::Type::CONST_INTEGER);
				}
			}
			else if ( tmp->type() == Token::Type::CONST_DOUBLE ) {
				// CONST_DOUBLE 'd'
				numCombines++;
			}
			else if ( tmp->type() == Token::Type::CONST_FLOAT ) {
				// CONST_FLOAT 'f'
				numCombines++;
			}
			else if ( tmp->type() == Token::Type::CONST_INTEGER ) {
				// CONST_INTEGER 'i'
				numCombines++;
			}

			if ( numCombines > 0 ) {
				// we found an operator
				TokenList::iterator opToken = token;
				++token;	// advance to next token

				while ( numCombines > 0 ) {
					numCombines--;	// decrement combinations

					opToken->resetContentTo((*opToken).content() + token->content());	// combine token contents
					opToken->resetTypeTo(token->type());    // and reset our opToken's type

					mTokens.erase(token++);	// remove the following token
				}

				continue;
			}
		}

		++token;
	}
}

/*
 * This merges all 'operator' tokens with their according operator (+, -, *, /, &, |, =, ==, <, <=, >, >=, etc.)
 */
void Tokenizer::replaceOperators()
{
	TokenIteratorMutable token = mTokens.begin();
	TokenIteratorMutable last = mTokens.end();

	// try to combine all operator tokens
	while ( token != mTokens.end() ) {
		if ( last != mTokens.end() && (last->category() == Token::Category::Assignment || last->category() == Token::Category::Operator) &&
				  token->type() == Token::Type::RESERVED_WORD && token->content() == RESERVED_WORD_OPERATOR ) {
			// we found an operator

			// retype current token ...
			token->resetTypeTo(Token::Type::IDENTIFER);
			token->resetContentTo(last->content() + RESERVED_WORD_OPERATOR);

			// ... and erase the previous one
			mTokens.erase(last);
		}
		else if ( last != mTokens.end() && last->type() == Token::Type::RESERVED_WORD && last->content() == RESERVED_WORD_OPERATOR ) {
			// previous token was an "operator" token

			// erase it ...
			mTokens.erase(last);

			// ... and retype current token
			token->resetTypeTo(Token::Type::IDENTIFER);
			token->resetContentTo(RESERVED_WORD_OPERATOR + (*token).content());
		}

		last = token++;
	}
}

const TokenList& Tokenizer::tokens() const
{
	return mTokens;
}


}
