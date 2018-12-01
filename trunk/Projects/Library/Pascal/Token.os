
// library imports

// project imports
import Position;


public enum TokenType {
	AND,
	ASSIGN,
	BEGIN,
	BOOLEAN,
	COLON,
	DOT,
	END,
	ELSE,
	EOF,
	EQUAL,
	FALSE,
	GREATER,
	GREATER_EQUAL,
	IDENTIFIER,
	IF,
	INTEGER,
	LESS,
	LESS_EQUAL,
	LPAREN,
	MATH_DIVIDE,
	MATH_DIVIDE_INT,
	MATH_MINUS,
	MATH_MULTIPLY,
	MATH_PLUS,
	OR,
	PRINT,
	PROGRAM,
	RPAREN,
	SEMICOLON,
	STRING,
	THEN,
	TRUE,
	UNEQUAL,
	UNIT,
	VAR,
	WHILE
	;
}

public string TokenToString(TokenType type val) {
	switch ( type ) {
		case TokenType.AND:			{ return "AND"; break; }
		case TokenType.ASSIGN:			{ return "ASSIGN"; break; }
		case TokenType.BEGIN:			{ return "BEGIN"; break; }
		case TokenType.BOOLEAN:			{ return "BOOLEAN"; break; }
		case TokenType.COLON:			{ return "COLON"; break; }
		case TokenType.DOT:			{ return "DOT"; break; }
		case TokenType.END:			{ return "END"; break; }
		case TokenType.ELSE:			{ return "ELSE"; break; }
		case TokenType.EOF:			{ return "EOF"; break; }
		case TokenType.EQUAL:			{ return "EQUAL"; break; }
		case TokenType.FALSE:			{ return "FALSE"; break; }
		case TokenType.GREATER:			{ return "GREATER"; break; }
		case TokenType.GREATER_EQUAL:		{ return "GREATER_EQUAL"; break; }
		case TokenType.IDENTIFIER:		{ return "IDENTIFIER"; break; }
		case TokenType.IF:			{ return "IF"; break; }
		case TokenType.INTEGER:			{ return "INTEGER"; break; }
		case TokenType.LESS:			{ return "LESS"; break; }
		case TokenType.LESS_EQUAL:		{ return "LESS_EQUAL"; break; }
		case TokenType.LPAREN:			{ return "("; break; }
		case TokenType.MATH_DIVIDE:		{ return "MATH_DIVIDE"; break; }
		case TokenType.MATH_DIVIDE_INT:		{ return "MATH_DIVIDE_INT"; break; }
		case TokenType.MATH_MINUS:		{ return "MATH_MINUS"; break; }
		case TokenType.MATH_MULTIPLY:		{ return "MATH_MULITPLY"; break; }
		case TokenType.MATH_PLUS:		{ return "MATH_PLUS"; break; }
		case TokenType.OR:			{ return "OR"; break; }
		case TokenType.PRINT:			{ return "PRINT"; break; }
		case TokenType.PROGRAM:			{ return "PROGRAM"; break; }
		case TokenType.RPAREN:			{ return ")"; break; }
		case TokenType.SEMICOLON:		{ return "SEMICOLON"; break; }
		case TokenType.STRING:			{ return "STRING"; break; }
		case TokenType.THEN:			{ return "THEN"; break; }
		case TokenType.TRUE:			{ return "TRUE"; break; }
		case TokenType.UNEQUAL:			{ return "UNEQUAL"; break; }
		case TokenType.UNIT:			{ return "UNIT"; break; }
		case TokenType.VAR:			{ return "VAR"; break; }
		case TokenType.WHILE:			{ return "WHILE"; break; }
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

