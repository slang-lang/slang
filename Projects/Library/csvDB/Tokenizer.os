
// library imports
import System.CharacterIterator;
import System.Collections.List;

// project imports
import Token;


public object Tokenizer {
	public void Constructor() {
		CHARS = new String( "ABCDEFGHIJKLMNOPRSTUVWXYZabcdefghijklmnoprstuvwxyz_" );
		DIGITS = new String( "0123456789" );
		OPERATORCHARS = new String( "+-*/%<>=" );

		RESERVED_WORDS = new List<Token>();
		RESERVED_WORDS.push_back( new Token( TokenType.AND, "AND", Position null ) );
		RESERVED_WORDS.push_back( new Token( TokenType.BOOLEAN, "FALSE", Position null ) );
		RESERVED_WORDS.push_back( new Token( TokenType.BOOLEAN, "TRUE", Position null ) );
		RESERVED_WORDS.push_back( new Token( TokenType.ELSE, "ELSE", Position null ) );
		RESERVED_WORDS.push_back( new Token( TokenType.EXPLAIN, "EXPLAIN", Position null ) );
		RESERVED_WORDS.push_back( new Token( TokenType.FROM, "FROM", Position null ) );
		RESERVED_WORDS.push_back( new Token( TokenType.IF, "IF", Position null ) );
		RESERVED_WORDS.push_back( new Token( TokenType.LIMIT, "LIMIT", Position null ) );
		RESERVED_WORDS.push_back( new Token( TokenType.OR, "OR", Position null ) );
		RESERVED_WORDS.push_back( new Token( TokenType.SELECT, "SELECT", Position null ) );
		RESERVED_WORDS.push_back( new Token( TokenType.THEN, "THEN", Position null ) );
		//RESERVED_WORDS.push_back( new Token( TokenType.TYPE, "BOOLEAN", Position null ) );
		//RESERVED_WORDS.push_back( new Token( TokenType.TYPE, "INTEGER", Position null ) );
		//RESERVED_WORDS.push_back( new Token( TokenType.TYPE, "REAL", Position null ) );
		//RESERVED_WORDS.push_back( new Token( TokenType.TYPE, "STRING", Position null ) );
		RESERVED_WORDS.push_back( new Token( TokenType.WHERE, "WHERE", Position null ) );

		WHITESPACES = new String( " 	" );
		WHITESPACES = WHITESPACES + LINEBREAK_DOS;
		WHITESPACES = WHITESPACES + LINEBREAK_UNIX;
	}

	public List<Token> parse( string query ) modify throws {
		mCharIterator = new CharacterIterator( query );
		mColumn       = 1;
		mLine         = 1;

		var tokens = new List<Token>();
		Token token;

		while ( (token = getNextToken()) != null ) {
			tokens.push_back(token);
		}

		tokens.push_back( new Token( TokenType.EOF, cast<string>( EOF ), new Position( mLine, mColumn ) ) );

		return tokens;
	}

	private string consume( int length = 1 ) modify {
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
		return new Position( mLine, mColumn );
	}

	private Token getDigit() modify {
		string result;

		while ( isDigit( peek() ) ) {
			result += consume();
		}

		return new Token( TokenType.INTEGER, result, getCurrentPos() );
	}

	private Token getID() modify throws {
		int column = mColumn;
		string result;

		string c;
		while ( (c = peek()) && ( isCharacter( c ) || isDigit( c ) ) ) {
			result += consume();
		}

		// convert to upper case
		//result = toUpper( result );

		foreach ( Token token : RESERVED_WORDS ) {
			if ( token == toUpper( result ) ) {
				return new Token( token.mType, token.mValue, new Position( mLine, column ) );
			}
		}

		return new Token( TokenType.IDENTIFIER, result, new Position( mLine, column ) );
	}

	private Token getNextToken() modify throws {
		string c;

		while ( (c = peek()) != "" ) {
			switch ( true ) {
				case isCharacter( c ): {
					return getID();
				}
				case isDigit( c ): {
					return getDigit();
				}
				case isWhiteSpace( c ): {
					consume();
					break;
				}
				case c == "\"": {
					var column = mColumn;
					var line   = mLine;

					consume();			// consume '

					string value;
					while ( peek() != "\"" ) {
						value += consume();
					}

					consume();			// consume '

					return new Token( TokenType.STRING, value, new Position( line, column ) );
				}
				case c == LINEBREAK_DOS || c == LINEBREAK_UNIX: {
					consume();	// consume linebreak
					return new Token( TokenType.LINEBREAK, "", new Position( mLine, mColumn ) );
				}
				case c == "=": {
					return new Token( TokenType.ASSIGN, consume(), new Position( mLine, mColumn ) );
				}
				case c == ":": {
					return new Token( TokenType.COLON, consume(), new Position( mLine, mColumn ) );
				}
				case c == ";": {
					return new Token( TokenType.SEMICOLON, consume(), new Position( mLine, mColumn ) );
				}
				case c == ",": {
					return new Token( TokenType.COMMA, consume(), new Position( mLine, mColumn ) );
				}
				case c == ".": {
					return new Token( TokenType.DOT, consume(), new Position( mLine, mColumn ) );
				}

				// Compare operators
				case c == "=": {
					return new Token( TokenType.EQUAL, consume(), new Position( mLine, mColumn ) );
				}
				case c == "<" && peek( 2 ) == ">": {
					return new Token( TokenType.UNEQUAL, consume( 2 ), new Position( mLine, mColumn ) );
				}
				case c == "<" && peek( 2 ) == "=": {
					return new Token( TokenType.LESS_EQUAL, consume( 2 ), new Position( mLine, mColumn ) );
				}
				case c == "<": {
					return new Token( TokenType.LESS, consume(), new Position( mLine, mColumn ) );
				}
				case c == ">" && peek( 2 ) == "=": {
					return new Token( TokenType.GREATER_EQUAL, consume( 2 ), new Position( mLine, mColumn ) );
				}
				case c == ">": {
					return new Token( TokenType.GREATER, consume(), new Position( mLine, mColumn ) );
				}

				// Arithmetic operators
				case c == "+": {
					return new Token( TokenType.MATH_PLUS, consume(), new Position( mLine, mColumn ) );
				}
				case c == "-": {
					return new Token( TokenType.MATH_MINUS, consume(), new Position( mLine, mColumn ) );
				}
				case c == "*": {
					return new Token( TokenType.MATH_MULTIPLY, consume(), new Position( mLine, mColumn ) );
				}
				case c == "/": {
					return new Token( TokenType.MATH_DIVIDE, consume(), new Position( mLine, mColumn ) );
				}
				case c == "(": {
					return new Token( TokenType.LPAREN, consume(), new Position( mLine, mColumn ) );
				}
				case c == ")": {
					return new Token( TokenType.RPAREN, consume(), new Position( mLine, mColumn ) );
				}
				default: {
					throw new Exception( "invalid token '" + c + "' found at " + new Position( mLine, mColumn ).toString() );
				}
			}
		}
	}

	private bool hasNext() const {
		return mCharIterator.hasNext();
	}

	private bool isCharacter( string char ) const {
		return CHARS.Contains( char );
	}

	private bool isDigit( string char ) const {
		return DIGITS.Contains( char );
	}

	private bool isWhiteSpace( string char ) const {
		return WHITESPACES.Contains( char );
	}

	private string peek(int pos = 1) const throws {
		try { return mCharIterator.peek( pos ); }

		return "";
	}

	private void skipWhiteSpace() modify {
		string c;

		while ( isWhiteSpace( c = peek() ) ) {
			print( "skipping whitespace" );
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
