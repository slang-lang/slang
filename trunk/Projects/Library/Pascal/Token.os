
// library imports

// project imports
import Position;


public enum TokenType {
	ASSIGN,
	BEGIN,
	DIVIDE,
	DOT,
	END,
	ELSE,
	EOF,
	EQUALS,
	IDENTIFIER,
	IF,
	INTEGER,
	LPAREN,
	MINUS,
	MULTIPLY,
	PLUS,
	PRINT,
	PROGRAM,
	RPAREN,
	SEMICOLON,
	STRING,
	THEN,
	UNIT
	;
}

public string TokenToString(TokenType type val) {
	switch ( type ) {
		case TokenType.ASSIGN:		{ return "ASSIGN"; break; }
		case TokenType.BEGIN:		{ return "BEGIN"; break; }
		case TokenType.DIVIDE:		{ return "DIVIDE"; break; }
		case TokenType.DOT:		{ return "DOT"; break; }
		case TokenType.END:		{ return "END"; break; }
		case TokenType.ELSE:		{ return "ELSE"; break; }
		case TokenType.EOF:		{ return "EOF"; break; }
		case TokenType.EQUALS:		{ return "EQUALS"; break; }
		case TokenType.IDENTIFIER:	{ return "IDENTIFIER"; break; }
		case TokenType.IF:		{ return "IF"; break; }
		case TokenType.INTEGER:		{ return "INTEGER"; break; }
		case TokenType.LPAREN:		{ return "("; break; }
		case TokenType.MINUS:		{ return "MINUS"; break; }
		case TokenType.MULTIPLY:	{ return "MULITPLY"; break; }
		case TokenType.PLUS:		{ return "PLUS"; break; }
		case TokenType.PRINT:		{ return "PRINT"; break; }
		case TokenType.PROGRAM:		{ return "PROGRAM"; break; }
		case TokenType.RPAREN:		{ return ")"; break; }
		case TokenType.SEMICOLON:	{ return "SEMICOLON"; break; }
		case TokenType.STRING:		{ return "STRING"; break; }
		case TokenType.THEN:		{ return "THEN"; break; }
		case TokenType.UNIT:		{ return "UNIT"; break; }
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

		//print(toString());
	}

	public string toString() const {
		return "Token(" + TokenToString(mType) + ", \"" + mValue + "\", " + mPosition ? mPosition.toString() : "<null>" + ")";
	}

	public bool operator==(string other) const {
		return mValue == other;
	}
}

