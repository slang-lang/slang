
// library imports

// project imports
import Position;


public enum TokenType {
	AND,
	ASSIGN,
	BOOLEAN,
	COLON,
	COMMA,
	DOT,
	ELSE,
	EOF,
	EQUAL,
	FALSE,
	FROM,
	GREATER,
	GREATER_EQUAL,
	IDENTIFIER,
	IF,
	INTEGER,
	LIMIT,
	LINEBREAK,
	LINECOMMENT,
	LESS,
	LESS_EQUAL,
	LPAREN,
	MATH_DIVIDE,
	MATH_MINUS,
	MATH_MULTIPLY,
	MATH_PLUS,
	OR,
	REAL,
	RPAREN,
	SELECT,
	SEMICOLON,
	STRING,
	THEN,
	TRUE,
	TYPE,
	UNEQUAL,
	WHERE
	;
}

public string TokenToString(TokenType type) {
	switch ( type ) {
		case TokenType.AND:			{ return "AND"; }
		case TokenType.ASSIGN:			{ return "="; }
		case TokenType.BOOLEAN:			{ return "BOOLEAN"; }
		case TokenType.COLON:			{ return ":"; }
		case TokenType.COMMA:			{ return "COMMA"; }
		case TokenType.DOT:			{ return "."; }
		case TokenType.ELSE:			{ return "ELSE"; }
		case TokenType.EOF:			{ return "EOF"; }
		case TokenType.EQUAL:			{ return "="; }
		case TokenType.FALSE:			{ return "FALSE"; }
		case TokenType.FROM:			{ return "FROM"; }
		case TokenType.GREATER:			{ return ">"; }
		case TokenType.GREATER_EQUAL:		{ return ">="; }
		case TokenType.IDENTIFIER:		{ return "IDENTIFIER"; }
		case TokenType.IF:			{ return "IF"; }
		case TokenType.INTEGER:			{ return "INTEGER"; }
		case TokenType.LIMIT:		{ return "LIMIT"; }
		case TokenType.LINEBREAK:		{ return "LINEBREAK"; }
		case TokenType.LINECOMMENT:		{ return "#"; }
		case TokenType.LESS:			{ return "<"; }
		case TokenType.LESS_EQUAL:		{ return "<="; }
		case TokenType.LPAREN:			{ return "("; }
		case TokenType.MATH_DIVIDE:		{ return "MATH_DIVIDE"; }
		case TokenType.MATH_MINUS:		{ return "MATH_MINUS"; }
		case TokenType.MATH_MULTIPLY:		{ return "MATH_MULITPLY"; }
		case TokenType.MATH_PLUS:		{ return "MATH_PLUS"; }
		case TokenType.OR:			{ return "OR"; }
		case TokenType.REAL:			{ return "REAL"; }
		case TokenType.RPAREN:			{ return ")"; }
		case TokenType.SELECT:			{ return "SELECT"; }
		case TokenType.SEMICOLON:		{ return ";"; }
		case TokenType.STRING:			{ return "STRING"; }
		case TokenType.THEN:			{ return "THEN"; }
		case TokenType.TRUE:			{ return "TRUE"; }
		case TokenType.TYPE:			{ return "TYPE"; }
		case TokenType.UNEQUAL:			{ return "<>"; }
		case TokenType.WHERE:			{ return "WHERE"; }
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

	public string =operator( string ) const {
	   return toString();
	}
}
