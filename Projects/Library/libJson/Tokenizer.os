
// library imports
import System.CharacterIterator;
import System.Collections.Vector;
import System.IO.File;

// project imports
import Token;


public namespace Json { }

public object Tokenizer {
	public void Constructor() {
		CHARS = new String( "ABCDEFGHIJKLMNOPRSTUVWXYZabcdefghijklmnoprstuvwxyz_" );
		DIGITS = new String( "0123456789.-+e" );

		RESERVED_WORDS = new Vector<Token>();
		RESERVED_WORDS.push_back( new Token( TokenType.BOOLEAN, "false", Position null ) );
		RESERVED_WORDS.push_back( new Token( TokenType.BOOLEAN, "true",  Position null ) );
		RESERVED_WORDS.push_back( new Token( TokenType.NULL,    "null",  Position null ) );

		WHITESPACES = new String( " 	" + LINEBREAK_DOS + LINEBREAK_UNIX );
	}

	public Vector<Token> parseString( string text ) modify {
		mCharIterator = new CharacterIterator( text );
		mColumn = 1;
		mLine = 1;

		var tokens = new Vector<Token>();

		Token token;
		while ( ( token = getNextToken() ) != null ) {
			tokens.push_back( token );
		}

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

		return new Token( TokenType.NUMBER, result, getCurrentPos() );
	}

	private Token getID() modify throws {
		int column = mColumn;
		string result;

		string c;
		while ( ( c = peek() ) && ( isCharacter( c ) || isDigit( c ) ) ) {
			result += consume();
		}

		// convert to upper case
		//result = toUpper( result );

		foreach ( Token token : RESERVED_WORDS ) {
			if ( token == toLower( result ) ) {
				return new Token( token.type, token.value, new Position( mLine, column ) );
			}
		}

		return new Token( TokenType.IDENTIFIER, result, new Position( mLine, column ) );
	}

	private Token getNextToken() modify throws {
		string c;

		while ( ( c = peek() ) != "" ) {
			switch ( true ) {
				case isCharacter( c ): {
					return getID();
				}
				case isDigit( c ) || c == "+" || c == "-": {
					return getDigit();
				}
				case isWhiteSpace( c ): {
					consume();
					break;
				}
				case c == "\"": {
					return new Token( TokenType.STRING, readString(), new Position( mLine, mColumn ) );
				}
				case c == ":": {
					return new Token( TokenType.COLON, consume(), new Position( mLine, mColumn ) );
				}
				case c == ",": {
					return new Token( TokenType.COMMA, consume(), new Position( mLine, mColumn ) );
				}
				case c == "[": {
					return new Token( TokenType.BRACKET_OPEN, consume(), new Position( mLine, mColumn ) );
				}
				case c == "]": {
					return new Token( TokenType.BRACKET_CLOSE, consume(), new Position( mLine, mColumn ) );
				}
				case c == "{": {
					return new Token( TokenType.CURLY_BRACKET_OPEN, consume(), new Position( mLine, mColumn ) );
				}
				case c == "}": {
					return new Token( TokenType.CURLY_BRACKET_CLOSE, consume(), new Position( mLine, mColumn ) );
				}
				default: {
					throw new Exception( "invalid token found at " + new Position( mLine, mColumn ).toString());
				}
			}
		}
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

	private string peek( int pos = 1 ) const throws {
		try {
			return mCharIterator.peek( pos );
		}

		return "";
	}

	private string readNumber() modify {
		string result;

		string char;
		while ( ( char = peek() ) && isDigit( char ) ) {
			result += consume();
		}

		if ( char == "." ) {
			result += char;

			while ( ( char = peek() ) && isDigit( char ) ) {
				result += consume();
			}
		}

		if ( char == "e" || char == "E" ) {
			result += char;

			if ( peek() == "." ) {
				result += consume();
			}

			while ( ( char = peek() ) && isDigit( char ) ) {
				result += consume();
			}
		}

		return result;
	}

	private string readString() modify {
		string ch = consume();		// consume "
		string value;
		while ( /*ch != "\\" &&*/ ( ch = mCharIterator.peek( 1 ) ) != "\"" ) {
			if ( ch == "\\" ) {
				ch = consume();
			}

			value += consume();
		}

		consume();			// consume "

		return value;
	}

	private void skipWhiteSpace() modify {
		string c;

		while ( isWhiteSpace( c = peek() ) ) {
			consume();
		}
	}

	// Private constants
	private String CHARS const;
	private String DIGITS const;
	private String COMPARECHARS const;
	private String DELIMITERCHARS const;
	private Vector<Token> RESERVED_WORDS const;
	private String WHITESPACES const;

	// Private members
	private CharacterIterator mCharIterator;
	private int mColumn;
	private int mLine;
}

