
// library imports

// project imports
import Position;


public namespace Json { }

public enum TokenType {
	BOOLEAN,
	BRACKET_CLOSE,
	BRACKET_OPEN,
	COLON,
	COMMA,
	CURLY_BRACKET_CLOSE,
	CURLY_BRACKET_OPEN,
	FALSE,
	IDENTIFIER,
	NULL,
	NUMBER,
	STRING,
	TRUE
	;
}

public string TokenToString( TokenType type ) {
	switch ( type ) {
		case TokenType.BOOLEAN:			{ return "BOOLEAN"; }
		case TokenType.BRACKET_CLOSE:	{ return "]"; }
		case TokenType.BRACKET_OPEN:	{ return "["; }
		case TokenType.COLON:			{ return ":"; }
		case TokenType.COMMA:			{ return ","; }
		case TokenType.CURLY_BRACKET_CLOSE:	{ return "}"; }
		case TokenType.CURLY_BRACKET_OPEN:	{ return "{"; }
		case TokenType.FALSE:			{ return "FALSE"; }
		case TokenType.IDENTIFIER:		{ return "IDENTIFIER"; }
		case TokenType.NULL:			{ return "NULL"; }
		case TokenType.NUMBER:			{ return "NUMBER"; }
		case TokenType.STRING:			{ return "STRING"; }
		case TokenType.TRUE:			{ return "TRUE"; }
	}

	return "<invalid token type>";
}


public object Token const {
	public Position position const;
	public TokenType type const;
	public string value const;

	public void Constructor( TokenType type_ const, string value_, Position position_ ) {
		position = position_;
		type = type_;
		value = value_;
	}

	public string toString() const {
		return "Token(" + TokenToString( type ) + ", \"" + value + "\", " + position ? position.toString() : "<null>" + ")";
	}

	public bool operator==( string other ) const {
		return value == other;
	}
}

