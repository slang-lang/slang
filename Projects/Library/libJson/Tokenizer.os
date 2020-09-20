
// library imports
import System.CharacterIterator;
import System.Collections.List;
import System.IO.File;

// project imports
import Token;


public namespace Json { }

public object Tokenizer {
	public void Constructor() {
		CHARS = new String( "ABCDEFGHIJKLMNOPRSTUVWXYZabcdefghijklmnoprstuvwxyz_" );
		DIGITS = new String( "0123456789" );

		RESERVED_WORDS = new List<Token>();
		RESERVED_WORDS.push_back( new Token( TokenType.BOOLEAN, "FALSE", Position null ) );
		RESERVED_WORDS.push_back( new Token( TokenType.BOOLEAN, "TRUE", Position null ) );
		RESERVED_WORDS.push_back( new Token( TokenType.NULL, "NULL", Position null ) );

		WHITESPACES = new String( " 	" );
		WHITESPACES = WHITESPACES + LINEBREAK_DOS;
		WHITESPACES = WHITESPACES + LINEBREAK_UNIX;
	}

	public Token currentToken() const {
		return mCurrentToken.current();
	}

	public bool hasNextToken() const {
		return mCurrentToken.hasNext();
	}

	public Token nextToken() modify {
		return mCurrentToken.next();
	}

	public void parseString( string text ) modify throws {
		mCharIterator = new String( text ).getIterator();
		mColumn = 1;
		mLine = 1;
		mTokens = new List<Token>();

		Token token;
		while ( ( token = getNextToken() ) != null ) {
			mTokens.push_back( token );
		}

		mCurrentToken = mTokens.getIterator();
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
		result = toUpper( result );

		foreach ( Token token : RESERVED_WORDS ) {
			if ( token == result ) {
				return new Token( token.mType, token.mValue, new Position( mLine, column ) );
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
				case isDigit( c ): {
					return getDigit();
				}
				case isWhiteSpace( c ): {
					consume();
					break;
				}
				case c == "\"": {
					int column = mColumn;
					int line = mLine;

					consume();			// consume "

					string value;
					while ( peek() != "\"" ) {
						value += consume();
					}

					consume();			// consume "

					return new Token( TokenType.STRING, value, new Position( line, column ) );
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

	private string peek( int pos = 1 ) const throws {
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
	private List<Token> RESERVED_WORDS const;
	private String WHITESPACES const;

	// Private members
	private CharacterIterator mCharIterator;
	private int mColumn;
	private Iterator<Token> mCurrentToken;
	private int mLine;
	private List<Token> mTokens;
}

