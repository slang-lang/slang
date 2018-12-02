
// library imports
import System.Collections.List;
import System.Collections.Map;
import System.IO.File;

// project imports
import Expressions;
import Statements;
import Token;
import Tokenizer;


public object ParseException const implements IException {
	public void Constructor(string msg, Position position const) {
		mMessage = msg;
		mPosition = position;
	}

	public string what() const {
		return mMessage + (mPosition ? " at " + string mPosition : "");
	}

	private string mMessage const;
	private Position mPosition const;
}


public object Parser {
	public Statement parseFile(string filename) modify throws {
		var tokenizer = new Tokenizer();

		mScope = new Map<string, bool>();
		mTokens = tokenizer.parseFile(filename);
		mTokenIterator = mTokens.getIterator();

		print("Building AST for \"" + filename + "\"...");

		Statement statement;

		Token token = consume();
		switch ( token ) {
			case "PROGRAM": {
				statement = Statement parseProgram();
				break;
			}
			case "UNIT": {
				statement = Statement parseUnit();
				break;
			}
		}

		return statement;
	}

	private AssignmentStatement parseAssignStatement() modify throws {
		Token identifier = peek();

		require(TokenType.IDENTIFIER);

		var identifierExp = Expression new VariableExpression(identifier, toUpper(identifier.mValue));

		require(TokenType.ASSIGN);

		var assignmentExp = expression();
		if ( !assignmentExp ) {
			throw new ParseException("invalid ASSIGNMENT expression found", identifier.mPosition);
		}

		return new AssignmentStatement(identifierExp, assignmentExp);
	}

	private CompoundStatement parseCompoundStatement() modify throws {
		//print("parseCompoundStatement()");

		Token token = consume();
		if ( !token || token.mType != TokenType.BEGIN ) {
			throw new ParseException("invalid COMPOUND statement found" + toString(token), token.mPosition);
		}

		var statements = new List<Statement>();
		while ( (token = peek()) != null && token.mType != TokenType.END ) {
			statements.push_back( parseStatement() );
		}

		require(TokenType.END);

		return new CompoundStatement( Object statements );
	}

	private ConstantDeclarationStatement parseConstantDeclarationStatement() modify throws {
		//print("parseConstantDeclarationStatement()");

		Token start = consume();
		if ( !start || start.mType != TokenType.CONST ) {
			throw new ParseException("invalid CONST statement found", start.mPosition);
		}

		var declStmt = parseDeclarationStatement();

		if ( mScope.contains(declStmt.mName) ) {
			throw new ParseException("symbol '" + declStmt.mName + "' already exists", start.mPosition);
		}

		mScope.insert(declStmt.mName, true);

		return new ConstantDeclarationStatement(
			declStmt
		);
	}


	private DeclarationStatement parseDeclarationStatement() modify throws {
		//print("parseDeclarationStatement()");

		Token identifier = consume();
		if ( !identifier || identifier.mType != TokenType.IDENTIFIER ) {
			throw new ParseException("invalid DECLARATION statement found", identifier.mPosition);
		}

		Token type;
		if ( peek().mType == TokenType.COLON ) {	// this allows using VAR without a typename
		require(TokenType.COLON);

		type = consume();
		if ( !type || type.mType != TokenType.IDENTIFIER ) {
			throw new ParseException("invalid TYPE found", type.mPosition);
		}
		}

		Expression value;

		Token assign = peek();
		if ( assign && assign.mType == TokenType.ASSIGN ) {
			consume();

			value = expression();
		}

		return new DeclarationStatement(
			identifier.mValue,
			type ? type.mValue : "",
			value
		);
	}

	private IfStatement parseIfStatement() modify throws {
		//print("parseIfStatement()");

		Token ifToken = peek();
		require(TokenType.IF);

		var conditionExp = expression();
		if ( !conditionExp ) {
			throw new ParseException("invalid conditional expression found", ifToken.mPosition);
		}

		require(TokenType.THEN);

		Statement ifBlock = parseStatement(false);
		Statement elseBlock;

		Token elseToken = peek();
		if ( elseToken && elseToken.mType == TokenType.ELSE ) {
			consume();

			elseBlock = parseStatement(false);
		}

		return new IfStatement(conditionExp, ifBlock, elseBlock);
	}

	private PrintStatement parsePrintStatement() modify throws {
		//print("parsePrintStatement()");

		require(TokenType.PRINT);

		return new PrintStatement( parseExpression() );
	}

	private ProgramStatement parseProgram() modify throws {
		//print("parseProgram()");

		Token name = consume();
		if ( !name || name.mType != TokenType.IDENTIFIER ) {
			throw new ParseException("invalid PROGRAM statement found" + toString(name), name.mPosition);
		}

		require(TokenType.SEMICOLON);

		var statement = new ProgramStatement(
			name.mValue,
			parseCompoundStatement()
		);

		require(TokenType.DOT);

		return statement;
	}

	private Statement parseStatement(bool requiresSemicolon = true) modify throws {
		//print("parseStatement()");

		Statement stmt;

		Token token = peek();
		switch ( token.mType ) {
			case TokenType.BEGIN: {
				stmt = Statement parseCompoundStatement();
				break;
			}
			case TokenType.CONST: {
				stmt = Statement parseConstantDeclarationStatement();
				break;
			}
			case TokenType.IDENTIFIER: {
				stmt = Statement parseAssignStatement();
				break;
			}
			case TokenType.IF: {
				stmt = Statement parseIfStatement();
				break;
			}
			case TokenType.PRINT: {
				stmt = Statement parsePrintStatement();
				break;
			}
			case TokenType.VAR: {
				stmt = Statement parseVariableDeclarationStatement();
				break;
			}
			case TokenType.WHILE: {
				stmt = Statement parseWhileStatement();
				break;
			}
			default: {
				throw new ParseException("invalid token found" + toString(token), token.mPosition);
			}
		}

		if ( requiresSemicolon ) {
			require(TokenType.SEMICOLON);
		}

		return stmt;
	}

	private UnitStatement parseUnit() modify throws {
		//print("parseUnit()");

		Token name = consume();
		if ( !name || name.mType != TokenType.IDENTIFIER ) {
			throw new ParseException("invalid UNIT statement found", name.mPosition);
		}

		require(TokenType.SEMICOLON);

		var statement = new UnitStatement(
			name.mValue,
			parseCompoundStatement()
		);

		require(TokenType.SEMICOLON);

		return statement;
	}

	private VariableDeclarationStatement parseVariableDeclarationStatement() modify throws {
		//print("parseVariableDeclarationStatement()");

		Token start = consume();
		if ( !start || start.mType != TokenType.VAR ) {
			throw new ParseException("invalid VAR statement found", start.mPosition);
		}

		var declStmt = parseDeclarationStatement();

		if ( mScope.contains(declStmt.mName) ) {
			throw new ParseException("symbol '" + declStmt.mName + "' already exists", start.mPosition);
		}

		mScope.insert(declStmt.mName, true);

		return new VariableDeclarationStatement(
			declStmt
		);
	}

	private WhileStatement parseWhileStatement() modify throws {
		//print("parseWhileStatement()");

		Token start = consume();
		if ( !start || start.mType != TokenType.WHILE ) {
			throw new ParseException("invalid WHILE statement found", start.mPosition);
		}

		var condition = expression();

		require(TokenType.DO);

		return new WhileStatement(
			condition,
			parseStatement(false)
		);
	}


//////////////////////////////////////////////////////////////////////////////
// Expression parsing

	private Expression expression() modify {
		//print("expression()");

		Expression node = parseCondition();

		Token op;
		while ( (op = peek()) != null && (op.mType == TokenType.AND || op.mType == TokenType.OR) ) {
			consume();

			Expression exp = Expression new BooleanBinaryExpression(op, node, op.mValue, parseCondition());
			node = exp;
		}

		return node;
	}

	private Expression parseCondition() modify throws {
		//print("parseCondition()");

		Expression node = parseExpression();

		Token op;
		while ( (op = peek()) != null && isComperator(op) ) {
			consume();

			Expression exp = Expression new BooleanBinaryExpression(op, node, op.mValue, parseExpression());
			node = exp;
		}

		return node;
	}

	private Expression parseExpression() modify throws {
		//print("parseExpression()");

		Expression node = parseTerm();

		Token op;
		while ( (op = peek()) != null && (op.mType == TokenType.MATH_MINUS || op.mType == TokenType.MATH_PLUS) ) {
			consume();

			Expression exp = Expression new BinaryExpression(op, node, op.mValue, parseTerm());
			node = exp;
		}

		return node;
	}

	private Expression parseFactor() modify throws {
		//print("parseFactor()");

		Token token = peek();
		switch ( token.mType ) {
			case TokenType.BOOLEAN: {
				require(TokenType.BOOLEAN);
				return Expression new ConstBooleanExpression(token, token.mValue == "TRUE");
			}
			case TokenType.IDENTIFIER: {
				return Expression parseIdentifier();
			}
			case TokenType.INTEGER: {
				require(TokenType.INTEGER);
				return Expression new ConstIntegerExpression(token, int token.mValue);
			}
			case TokenType.LPAREN: {
				require(TokenType.LPAREN);
				Expression node = expression();
				require(TokenType.RPAREN);

				return node;
			}
			case TokenType.MATH_MINUS: {
				require(TokenType.MATH_MINUS);
				return Expression new UnaryExpression(token, token.mValue, parseFactor());	
			}
			case TokenType.MATH_PLUS: {
				require(TokenType.MATH_PLUS);
				return Expression new UnaryExpression(token, token.mValue, parseFactor());	
			}
			case TokenType.STRING: {
				require(TokenType.STRING);
				return Expression new ConstStringExpression(token, token.mValue);
			}
			default: {
				return Expression parseIdentifier();
			}
		}

		throw new ParseException("invalid factor expression found" + toString(token), token.mPosition);
	}

	private Expression parseTerm() modify throws {
		//print("parseTerm()");

		Expression node = parseFactor();

		Token op;
		while ( (op = peek()) != null &&
			(op.mType == TokenType.MATH_DIVIDE
			|| op.mType == TokenType.MATH_DIVIDE_INT
			|| op.mType == TokenType.MATH_MULTIPLY) ) {
			consume();
			Expression exp = Expression new BinaryExpression(op, node, op.mValue, parseFactor());
			node = exp;
		}

		return node;
	}

	private Expression parseIdentifier() modify throws {
		//print("parseIdentifier()");

		Token token = consume();
		return Expression new VariableExpression(token, toUpper(token.mValue));
	}

// Expression parsing
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// Helpers

	private Token consume() modify throws {
		try { return mTokenIterator.next(); }

		return Token null;
	}

	private bool isComperator(Token token) const {
		switch ( token.mType ) {
			case TokenType.EQUAL:		{ return true; }
			case TokenType.GREATER:		{ return true; }
			case TokenType.GREATER_EQUAL:	{ return true; }
			case TokenType.LESS:		{ return true; }
			case TokenType.LESS_EQUAL:	{ return true; }
			case TokenType.UNEQUAL:		{ return true; }
			default:			{ return false; }
		}

		return false;
	}

	private Token peek(int pos = 1) const throws {
		try { return mTokenIterator.peek(pos); }

		return Token null;
	}

	private string toString(Expression exp) const {
		return "[" + (exp ? exp.toString() : "<invalid expression>") + "]";
	}

	private string toString(Statement stmt) const {
		return "[" + (stmt ? stmt.toString() : "<invalid statement>") + "]";
	}

	private string toString(Token token) const {
		return "[" + (token ? token.toString() : "<invalid token>") + "]";
	}

	private void require(TokenType tokenType const) modify throws {
		Token token = consume();

		if ( token.mType != tokenType ) {
			throw new ParseException(TokenToString(tokenType) + " expected but " + toString(token) + " found", token.mPosition);
		}
	}

// Helpers
//////////////////////////////////////////////////////////////////////////////


	private Map<string, bool> mScope;
	private Iterator<Token> mTokenIterator;
	private List<Token> mTokens;
}

