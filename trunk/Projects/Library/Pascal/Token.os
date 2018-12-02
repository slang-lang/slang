
// library imports

// project imports
import Position;


public enum TokenType {
	AND,
	ASSIGN,
	BEGIN,
	BOOLEAN,
	COLON,
	CONST,
	DO,
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
		case TokenType.AND:			{ return "AND"; }
		case TokenType.ASSIGN:			{ return "ASSIGN"; }
		case TokenType.BEGIN:			{ return "BEGIN"; }
		case TokenType.BOOLEAN:			{ return "BOOLEAN"; }
		case TokenType.CONST:                   { return "CONST"; }
		case TokenType.COLON:			{ return "COLON"; }
		case TokenType.DO:			{ return "DO"; }
		case TokenType.DOT:			{ return "DOT"; }
		case TokenType.END:			{ return "END"; }
		case TokenType.ELSE:			{ return "ELSE"; }
		case TokenType.EOF:			{ return "EOF"; }
		case TokenType.EQUAL:			{ return "EQUAL"; }
		case TokenType.FALSE:			{ return "FALSE"; }
		case TokenType.GREATER:			{ return "GREATER"; }
		case TokenType.GREATER_EQUAL:		{ return "GREATER_EQUAL"; }
		case TokenType.IDENTIFIER:		{ return "IDENTIFIER"; }
		case TokenType.IF:			{ return "IF"; }
		case TokenType.INTEGER:			{ return "INTEGER"; }
		case TokenType.LESS:			{ return "LESS"; }
		case TokenType.LESS_EQUAL:		{ return "LESS_EQUAL"; }
		case TokenType.LPAREN:			{ return "("; }
		case TokenType.MATH_DIVIDE:		{ return "MATH_DIVIDE"; }
		case TokenType.MATH_DIVIDE_INT:		{ return "MATH_DIVIDE_INT"; }
		case TokenType.MATH_MINUS:		{ return "MATH_MINUS"; }
		case TokenType.MATH_MULTIPLY:		{ return "MATH_MULITPLY"; }
		case TokenType.MATH_PLUS:		{ return "MATH_PLUS"; }
		case TokenType.OR:			{ return "OR"; }
		case TokenType.PRINT:			{ return "PRINT"; }
		case TokenType.PROGRAM:			{ return "PROGRAM"; }
		case TokenType.RPAREN:			{ return ")"; }
		case TokenType.SEMICOLON:		{ return "SEMICOLON"; }
		case TokenType.STRING:			{ return "STRING"; }
		case TokenType.THEN:			{ return "THEN"; }
		case TokenType.TRUE:			{ return "TRUE"; }
		case TokenType.UNEQUAL:			{ return "UNEQUAL"; }
		case TokenType.UNIT:			{ return "UNIT"; }
		case TokenType.VAR:			{ return "VAR"; }
		case TokenType.WHILE:			{ return "WHILE"; }
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

