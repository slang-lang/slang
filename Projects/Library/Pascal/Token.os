
// library imports

// project imports
import Position;


public enum TokenType {
	AND,
	ASSIGN,
	BEGIN,
	BOOLEAN,
	BREAK,
	CASE,
	COLON,
	COMMA,
	CONST,
	CONTINUE,
	DO,
	DOT,
	END,
	ELSE,
	EOF,
	EQUAL,
	EXIT,
	FALSE,
	FOR,
	FUNCTION,
	GREATER,
	GREATER_EQUAL,
	IDENTIFIER,
	IF,
	IMPLEMENTATION,
	INTERFACE,
	INTEGER,
	LINECOMMENT,
	LESS,
	LESS_EQUAL,
	LPAREN,
	MATH_DIVIDE,
	MATH_DIVIDE_INT,
	MATH_MINUS,
	MATH_MULTIPLY,
	MATH_PLUS,
	OF,
	OR,
	PROCEDURE,
	PROGRAM,
	READLN,
	REAL,
	REPEAT,
	RPAREN,
	SEMICOLON,
	STEP,
	STRING,
	THEN,
	TO,
	TRUE,
	TYPE,
	UNEQUAL,
	UNIT,
	UNTIL,
	USES,
	VAR,
	WHILE,
	WRITE,
	WRITELN
	;
}

public string TokenToString(TokenType type) {
	switch ( type ) {
		case TokenType.AND:			{ return "AND"; }
		case TokenType.ASSIGN:			{ return ":="; }
		case TokenType.BEGIN:			{ return "BEGIN"; }
		case TokenType.BOOLEAN:			{ return "BOOLEAN"; }
		case TokenType.BREAK:			{ return "BREAK"; }
		case TokenType.CASE:			{ return "CASE"; }
		case TokenType.COLON:			{ return ":"; }
		case TokenType.COMMA:			{ return ","; }
		case TokenType.CONST:                   { return "CONST"; }
		case TokenType.CONTINUE:                { return "CONTINUE"; }
		case TokenType.DO:			{ return "DO"; }
		case TokenType.DOT:			{ return "."; }
		case TokenType.END:			{ return "END"; }
		case TokenType.ELSE:			{ return "ELSE"; }
		case TokenType.EOF:			{ return "EOF"; }
		case TokenType.EQUAL:			{ return "="; }
		case TokenType.EXIT:			{ return "EXIT"; }
		case TokenType.FALSE:			{ return "FALSE"; }
		case TokenType.FOR:			{ return "FOR"; }
		case TokenType.FUNCTION:		{ return "FUNCTION"; }
		case TokenType.GREATER:			{ return ">"; }
		case TokenType.GREATER_EQUAL:		{ return ">="; }
		case TokenType.IDENTIFIER:		{ return "IDENTIFIER"; }
		case TokenType.IF:			{ return "IF"; }
		case TokenType.IMPLEMENTATION:		{ return "IMPLEMENTATION"; }
		case TokenType.INTERFACE:		{ return "INTERFACE"; }
		case TokenType.INTEGER:			{ return "INTEGER"; }
		case TokenType.LINECOMMENT:		{ return "#"; }
		case TokenType.LESS:			{ return "<"; }
		case TokenType.LESS_EQUAL:		{ return "<="; }
		case TokenType.LPAREN:			{ return "("; }
		case TokenType.MATH_DIVIDE:		{ return "MATH_DIVIDE"; }
		case TokenType.MATH_DIVIDE_INT:		{ return "MATH_DIVIDE_INT"; }
		case TokenType.MATH_MINUS:		{ return "MATH_MINUS"; }
		case TokenType.MATH_MULTIPLY:		{ return "MATH_MULITPLY"; }
		case TokenType.MATH_PLUS:		{ return "MATH_PLUS"; }
		case TokenType.OF:			{ return "OF"; }
		case TokenType.OR:			{ return "OR"; }
		case TokenType.PROCEDURE:		{ return "PROCEDURE"; }
		case TokenType.PROGRAM:			{ return "PROGRAM"; }
		case TokenType.READLN:			{ return "READLN"; }
		case TokenType.REAL:			{ return "REAL"; }
		case TokenType.REPEAT:			{ return "REPEAT"; }
		case TokenType.RPAREN:			{ return ")"; }
		case TokenType.SEMICOLON:		{ return ";"; }
		case TokenType.STEP:			{ return "STEP"; }
		case TokenType.STRING:			{ return "STRING"; }
		case TokenType.THEN:			{ return "THEN"; }
		case TokenType.TO:			{ return "TO"; }
		case TokenType.TRUE:			{ return "TRUE"; }
		case TokenType.TYPE:			{ return "TYPE"; }
		case TokenType.UNEQUAL:			{ return "<>"; }
		case TokenType.UNIT:			{ return "UNIT"; }
		case TokenType.UNTIL:			{ return "UNTIL"; }
		case TokenType.USES:			{ return "USES"; }
		case TokenType.VAR:			{ return "VAR"; }
		case TokenType.WHILE:			{ return "WHILE"; }
		case TokenType.WRITE:			{ return "WRITE"; }
		case TokenType.WRITELN:			{ return "WRITELN"; }
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

