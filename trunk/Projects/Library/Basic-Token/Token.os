
// library imports

// project imports
import Position;


public enum TokenType {
	AND,
	ASSIGN,
	BOOLEAN,
	COLON,
	COMMA,
	DIM,
	DOT,
	ELSE,
	END,
	EOF,
	EQUAL,
	FALSE,
	FOR,
	GREATER,
	GREATER_EQUAL,
	GOTO,
	IDENTIFIER,
	IF,
	INPUT,
	INTEGER,
	LINEBREAK,
	LINECOMMENT,
	LESS,
	LESS_EQUAL,
	LET,
	LPAREN,
	MATH_DIVIDE,
	MATH_MINUS,
	MATH_MULTIPLY,
	MATH_PLUS,
	NEXT,
	OR,
	PRINT,
	REAL,
	REM,
	RPAREN,
	SEMICOLON,
	STEP,
	STRING,
	THEN,
	TO,
	TRUE,
	TYPE,
	UNEQUAL
	;
}

public string TokenToString(TokenType type) {
	switch ( type ) {
		case TokenType.AND:			{ return "AND"; }
		case TokenType.ASSIGN:			{ return "="; }
		case TokenType.BOOLEAN:			{ return "BOOLEAN"; }
		case TokenType.COLON:			{ return ":"; }
		case TokenType.COMMA:			{ return ","; }
		case TokenType.DIM:			{ return "DIM"; }
		case TokenType.DOT:			{ return "."; }
		case TokenType.END:			{ return "END"; }
		case TokenType.ELSE:			{ return "ELSE"; }
		case TokenType.EOF:			{ return "EOF"; }
		case TokenType.EQUAL:			{ return "="; }
		case TokenType.FALSE:			{ return "FALSE"; }
		case TokenType.FOR:			{ return "FOR"; }
		case TokenType.GREATER:			{ return ">"; }
		case TokenType.GREATER_EQUAL:		{ return ">="; }
		case TokenType.GOTO:			{ return "GOTO"; }
		case TokenType.IDENTIFIER:		{ return "IDENTIFIER"; }
		case TokenType.IF:			{ return "IF"; }
		case TokenType.INPUT:			{ return "INPUT"; }
		case TokenType.INTEGER:			{ return "INTEGER"; }
		case TokenType.LINEBREAK:		{ return "LINEBREAK"; }
		case TokenType.LINECOMMENT:		{ return "#"; }
		case TokenType.LESS:			{ return "<"; }
		case TokenType.LESS_EQUAL:		{ return "<="; }
		case TokenType.LET:			{ return "LET"; }
		case TokenType.LPAREN:			{ return "("; }
		case TokenType.MATH_DIVIDE:		{ return "MATH_DIVIDE"; }
		case TokenType.MATH_MINUS:		{ return "MATH_MINUS"; }
		case TokenType.MATH_MULTIPLY:		{ return "MATH_MULITPLY"; }
		case TokenType.MATH_PLUS:		{ return "MATH_PLUS"; }
		case TokenType.NEXT:			{ return "NEXT"; }
		case TokenType.OR:			{ return "OR"; }
		case TokenType.REAL:			{ return "REAL"; }
		case TokenType.REM:			{ return "REM"; }
		case TokenType.RPAREN:			{ return ")"; }
		case TokenType.PRINT:			{ return "PRINT"; }
		case TokenType.SEMICOLON:		{ return ";"; }
		case TokenType.STEP:			{ return "STEP"; }
		case TokenType.STRING:			{ return "STRING"; }
		case TokenType.THEN:			{ return "THEN"; }
		case TokenType.TO:			{ return "TO"; }
		case TokenType.TRUE:			{ return "TRUE"; }
		case TokenType.TYPE:			{ return "TYPE"; }
		case TokenType.UNEQUAL:			{ return "<>"; }
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

