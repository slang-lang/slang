
// library imports

// project imports
import Position;


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
	TRUE,
	TYPE
	;
}

public string TokenToString(TokenType type) {
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
		case TokenType.TYPE:			{ return "TYPE"; }
	}

	return "<invalid token type>";
}


public object Token const {
	public Position mPosition const;
	public TokenType mType const;
	public string mValue const;

	public void Constructor(TokenType type const, string value, Position position) {
		mPosition = position;
		mType = type;
		mValue = value;
	}

	public string toString() const {
		return "Token(" + TokenToString(mType) + ", \"" + mValue + "\", " + mPosition ? mPosition.toString() : "<null>" + ")";
	}

	public bool operator==(string other) const {
		return mValue == other;
	}
}

