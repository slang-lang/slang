
// library imports
import System.CharacterIterator;
import System.Collections.List;
import System.IO.File;

// project imports
import Scanner;
import Token;


public object Tokenizer {
	public void Constructor() {
		CHARS = new String("ABCDEFGHIJKLMNOPRSTUVWXYZabcdefghijklmnoprstuvwxyz_");
		DIGITS = new String("0123456789");
		OPERATORCHARS = new String("+-*/%<>=");

		RESERVED_WORDS = new List<Token>();
		RESERVED_WORDS.push_back(new Token(TokenType.AND, "AND", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.BEGIN, "BEGIN", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.BOOLEAN, "FALSE", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.BOOLEAN, "TRUE", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.BREAK, "BREAK", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.CASE, "CASE", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.CONST, "CONST", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.CONTINUE, "CONTINUE", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.DO, "DO", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.END, "END", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.ELSE, "ELSE", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.EXIT, "EXIT", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.FOR, "FOR", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.FUNCTION, "FUNCTION", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.IF, "IF", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.IMPLEMENTATION, "IMPLEMENTATION", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.INTERFACE, "INTERFACE", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.MATH_DIVIDE_INT, "DIV", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.OF, "OF", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.OR, "OR", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.PROCEDURE, "PROCEDURE", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.PROGRAM, "PROGRAM", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.READLN, "READLN", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.REPEAT, "REPEAT", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.STEP, "STEP", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.THEN, "THEN", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.TO, "TO", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.TYPE, "BOOLEAN", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.TYPE, "INTEGER", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.TYPE, "REAL", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.TYPE, "STRING", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.UNIT, "UNIT", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.UNTIL, "UNTIL", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.USES, "USES", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.VAR, "VAR", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.WHILE, "WHILE", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.WRITE, "WRITE", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.WRITELN, "WRITELN", Position null));

		WHITESPACES = new String(" 	");
		WHITESPACES = WHITESPACES + LINEBREAK_DOS;
		WHITESPACES = WHITESPACES + LINEBREAK_UNIX;
	}

	public Token const getToken(string word) {
		foreach ( Token token : RESERVED_WORDS ) {
			if ( token == word ) {
				return token;
			}
		}

		return Token null;
	}

	public List<Token> parseFile(string filename, bool debug = false) modify throws {
		if ( debug ) {
			print("Tokenizing \"" + filename + "\"...");
		}

		mCharIterator = new Scanner(new System.IO.File(filename)).getIterator();
		mColumn = 1;
		mLine = 1;

		var tokens = new List<Token>();
		Token token;

		while ( (token = getNextToken()) != null ) {
			tokens.push_back(token);
		}

		return tokens;
	}

	private string consume(int length = 1) modify {
		string c;
		string result;

		while ( length > 0 ) {
			length--;

			c = mCharIterator.next();
			mColumn++;

			result += c;

			if ( c == LINEBREAK ) {
				mColumn = 1;
				mLine++;
			}
		}

		return result;
	}

	private Position getCurrentPos() const {
		return new Position(mLine, mColumn);
	}

	private Token getDigit() modify {
		string result;

		while ( isDigit(peek()) ) {
			result += consume();
		}

		return new Token(TokenType.INTEGER, result, getCurrentPos());
	}

	private Token getID() modify throws {
		int column = mColumn;
		string result;

		string c;
		while ( (c = peek()) && (isCharacter(c) || isDigit(c)) ) {
			result += consume();
		}

		// convert to upper case
		result = toUpper(result);

		foreach ( Token token : RESERVED_WORDS ) {
			if ( token == result ) {
				return new Token(token.mType, token.mValue, new Position(mLine, column));
			}
		}

		return new Token(TokenType.IDENTIFIER, result, new Position(mLine, column));
	}

	private Token getNextToken() modify throws {
		string c;
		bool isComment;

		while ( (c = peek()) != "" ) {
			if ( !isComment && c == "{" ) {
				consume();
				isComment = true;
			}
			else if ( isComment && c == "}" ) {
				consume();
				isComment = false;
			}
			else if ( isComment ) {
				consume();
			}
			else {
				switch ( true ) {
					case isCharacter(c) && !isComment: {
						return getID();
					}
					case isDigit(c) && !isComment: {
						return getDigit();
					}
					case isWhiteSpace(c): {
						consume();
						break;
					}
					case c == "'": {
						consume();			// consume '

						string value;
						while ( peek() != "\'" ) {
							value += consume();
						}

						consume();			// consume '

						return new Token(TokenType.STRING, value, new Position(mLine, mColumn));
					}
					case c == ":" && peek(2) == "=": {
						return new Token(TokenType.ASSIGN, consume(2), new Position(mLine, mColumn));
					}
					case c == ":": {
						return new Token(TokenType.COLON, consume(), new Position(mLine, mColumn));
					}
					case c == ";": {
						return new Token(TokenType.SEMICOLON, consume(), new Position(mLine, mColumn));
					}
					case c == ",": {
						return new Token(TokenType.COMMA, consume(), new Position(mLine, mColumn));
					}
					case c == ".": {
						return new Token(TokenType.DOT, consume(), new Position(mLine, mColumn));
					}

					// Compare operators
					case c == "=": {
						return new Token(TokenType.EQUAL, consume(), new Position(mLine, mColumn));
					}
					case c == "<" && peek(2) == ">": {
						return new Token(TokenType.UNEQUAL, consume(2), new Position(mLine, mColumn));
					}
					case c == "<" && peek(2) == "=": {
						return new Token(TokenType.LESS_EQUAL, consume(2), new Position(mLine, mColumn));
					}
					case c == "<": {
						return new Token(TokenType.LESS, consume(), new Position(mLine, mColumn));
					}
					case c == ">" && peek(2) == "=": {
						return new Token(TokenType.GREATER_EQUAL, consume(2), new Position(mLine, mColumn));
					}
					case c == ">": {
						return new Token(TokenType.GREATER, consume(), new Position(mLine, mColumn));
					}

					// Arithmetic operators
					case c == "+": {
						return new Token(TokenType.MATH_PLUS, consume(), new Position(mLine, mColumn));
					}
					case c == "-": {
						return new Token(TokenType.MATH_MINUS, consume(), new Position(mLine, mColumn));
					}
					case c == "*": {
						return new Token(TokenType.MATH_MULTIPLY, consume(), new Position(mLine, mColumn));
					}
					case c == "/": {
						return new Token(TokenType.MATH_DIVIDE, consume(), new Position(mLine, mColumn));
					}
					case c == "(": {
						return new Token(TokenType.LPAREN, consume(), new Position(mLine, mColumn));
					}
					case c == ")": {
						return new Token(TokenType.RPAREN, consume(), new Position(mLine, mColumn));
					}
					default: {
						throw new Exception("invalid token found at " + new Position(mLine, mColumn).toString());
					}
				}
			}
		}
	}

	private bool hasNext() const {
		return mCharIterator.hasNext();
	}

	private bool isCharacter(string char) const {
		return CHARS.Contains(char);
	}

	private bool isDigit(string char) const {
		return DIGITS.Contains(char);
	}

	private bool isWhiteSpace(string char) const {
		return WHITESPACES.Contains(char);
	}

	private string peek(int pos = 1) const throws {
		try { return mCharIterator.peek(pos); }

		return "";
	}

	private void skipWhiteSpace() modify {
		string c;

		while ( isWhiteSpace(c = peek()) ) {
			print("skipping whitespace");
			consume();
		}
	}

	// Private constants
	private String CHARS const;
	private String DIGITS const;
	private String COMPARECHARS const;
	private String DELIMITERCHARS const;
	private String OPERATORCHARS const;
	private List<Token> RESERVED_WORDS const;
	private String WHITESPACES const;

	// Private members
	private CharacterIterator mCharIterator;
	private int mColumn;
	private int mLine;
}

