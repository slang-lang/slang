
// library imports
import System.CharacterIterator;
import System.Collections.List;
import System.IO.File;

// project imports
import Scanner;
import Token;


public object Tokenizer {
	public void Constructor() {
		CHARS = new String("ABCDEFGHIJKLMNOPRSTUVWXYZabcdefghijklmnoprstuvwxyz");
		DIGITS = new String("0123456789");
		OPERATORCHARS = new String("+-*/%<>=");

		RESERVED_WORDS = new List<Token>();
		RESERVED_WORDS.push_back(new Token(TokenType.BEGIN, "BEGIN", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.END, "END", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.PRINT, "PRINT", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.PROGRAM, "PROGRAM", Position null));
		RESERVED_WORDS.push_back(new Token(TokenType.UNIT, "UNIT", Position null));

		WHITESPACES = new String(" 	");
		WHITESPACES = WHITESPACES + LINEBREAK_DOS;
		WHITESPACES = WHITESPACES + LINEBREAK_UNIX;

		print("");
	}

	public void Destructor() {
		// this is empty by intend
	}

	public List<Token> parseFile(string filename) modify throws {
		print("Parsing file \"" + filename + "\"...");

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
			mCharIterator.next();
			mColumn++;

			c = mCharIterator.current();
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

		while ( isCharacter(peek()) ) {
			result += consume();
		}

		foreach ( Token token : RESERVED_WORDS ) {
			if ( token == result ) {
				return new Token(token.mType, token.mValue, new Position(mLine, column));
			}
		}

		return new Token(TokenType.IDENTIFIER, result, new Position(mLine, column));
	}

	private Token getNextToken() modify throws {
		string c;

		while ( (c = peek()) != "" ) {
			switch ( true ) {
				case isCharacter(c): {
					return getID();
				}
				case isDigit(c): {
					return getDigit();
				}
				case isWhiteSpace(c): {
					consume();
					break;
				}
				case c == "'": {
					int column = mColumn;
					int line = mLine;

					consume();			// consume '

					string value;
					while ( peek() != "\'" ) {
						value += consume();
					}

					consume();			// consume '

					return new Token(TokenType.STRING, value, new Position(line, column));
				}
				case c == ":" && peek(2) == "=": {
					return new Token(TokenType.ASSIGN, consume(2), new Position(mLine, mColumn));
				}
				case c == ";": {
					return new Token(TokenType.SEMICOLON, consume(), new Position(mLine, mColumn));
				}
				case c == ".": {
					return new Token(TokenType.DOT, consume(), new Position(mLine, mColumn));
				}
				case c == "+": {
					return new Token(TokenType.PLUS, consume(), new Position(mLine, mColumn));
				}
				case c == "-": {
					return new Token(TokenType.MINUS, consume(), new Position(mLine, mColumn));
				}
				case c == "*": {
					return new Token(TokenType.MULTIPLY, consume(), new Position(mLine, mColumn));
				}
				case c == "/": {
					return new Token(TokenType.DIVIDE, consume(), new Position(mLine, mColumn));
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
		try { return mCharIterator.lookAHead(pos); }

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
	private List<Token> RESERVED_WORDS;
	private String WHITESPACES const;

	// Private members
	private CharacterIterator mCharIterator;
	private int mColumn;
	private int mLine;
}

