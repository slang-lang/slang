
// library imports
import System.Collections.List;
import System.Collections.Map;
import System.IO.File;

// project imports
import Expressions;
import Statements;
import SymbolTable;
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
	public Statement parseFile(string filename, bool debug = false) modify throws {
		var tokenizer = new Tokenizer();

		mTokenizer = new Tokenizer();
		mTokens = tokenizer.parseFile(filename, debug);
		mTokenIterator = mTokens.getIterator();

		if ( debug ) {
			print("Building AST for \"" + filename + "\"...");
		}

		Statement statement;

		Token token = consume();
		switch ( token.mValue ) {
			case "PROGRAM": {
				statement = Statement parseProgram();
				break;
			}
			case "UNIT": {
				statement = Statement parseUnit();
				break;
			}
			default: {
				throw new ParseException("invalid token detected", token.mPosition);
			}
		}

		return statement;
	}

	private AssignmentStatement parseAssignStatement() modify throws {
		//print("parseAssignment()");

		Token identifier = peek();

		require(TokenType.IDENTIFIER);

		var sym = mCurrentScope.lookup(identifier.mValue);
		if ( !sym ) {
			throw new ParseException("Symbol '" + identifier.mValue + "' is unknown", identifier.mPosition);
		}
		if ( !(sym is LocalSymbol) ) {
			throw new ParseException("Symbol '" + identifier.mValue + "' is not of type LocalSymbol", identifier.mPosition);
		}
		if ( (LocalSymbol sym).mIsConst ) {
			throw new ParseException("Assignment to const Symbol '" + identifier.mValue + "' is not allowed", identifier.mPosition);
		}

		var identifierExp = Expression new VariableExpression(identifier, toUpper(identifier.mValue), (LocalSymbol sym).mType);

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

	private CompoundStatement parseCompoundStatementWithDeclarations() modify throws {
		//print("parseCompoundStatementWithDeclarations()");

		var constStmt = parseConstantDeclarationStatement();
		var varStmt = parseVariableDeclarationStatement();

		var methods = new List<ScopeStatement>();
		Token token;
		while ( (token = peek()) != null ) {
			ScopeStatement stmt;
			if ( token.mType == TokenType.FUNCTION ) {
				stmt = parseFunction();
			}
			else if ( token.mType == TokenType.PROCEDURE ) {
				stmt = parseProcedure();
			}
			else {
				break;
			}

			methods.push_back( stmt );
		}

		var stmt = parseCompoundStatement();
		stmt.mConstantDeclarations = constStmt;
		stmt.mMethods = methods;
		stmt.mVariableDeclarations = varStmt;

		return stmt;
	}

	private ConstantDeclarationStatement parseConstantDeclarationStatement() modify throws {
		//print("parseConstantDeclarationStatement()");

		var stmt = new ConstantDeclarationStatement();

		Token start = peek();
		if ( start && start.mType == TokenType.CONST ) {
			consume();	// consume CONST token

			while ( peek().mType == TokenType.IDENTIFIER ) {
				var declStmt = parseDeclarationStatement();
				stmt.mDeclarations.push_back( declStmt );

				if ( mCurrentScope.lookup(declStmt.mName, true) ) {
					throw new ParseException("symbol '" + declStmt.mName + "' already exists", start.mPosition);
				}

				mCurrentScope.declare(Symbol new LocalSymbol(declStmt.mName, declStmt.mType, true));
			}
		}

		return stmt;
	}

	private DeclarationStatement parseDeclarationStatement(bool requireSemicolon = true) modify throws {
		//print("parseDeclarationStatement()");

		Token identifier = consume();
		if ( !identifier || identifier.mType != TokenType.IDENTIFIER ) {
			throw new ParseException("invalid DECLARATION statement found", identifier.mPosition);
		}

		require(TokenType.COLON);

		Token type = consume();
		if ( !type || type.mType != TokenType.TYPE ) {
			throw new ParseException("invalid TYPE found", type.mPosition);
		}

		Expression value;

		Token assign = peek();
		if ( assign && assign.mType == TokenType.ASSIGN ) {
			consume();

			value = expression();
		}

		if ( requireSemicolon ) {
			require(TokenType.SEMICOLON);
		}

		return new DeclarationStatement(
			identifier.mValue,
			type ? type.mValue : "",
			value
		);
	}

	private ScopeStatement parseFunction() modify throws {
		//print("parseFunction()");

		require(TokenType.FUNCTION);

		// name
		Token name = consume();
		if ( name.mType != TokenType.IDENTIFIER ) {
			throw new ParseException("invalid token " + toString(name) + " found", name.mPosition);
		}

		List<DeclarationStatement> declarations;

		Token token = peek();
		if ( token.mType == TokenType.LPAREN ) {
			require(TokenType.LPAREN);

			declarations = parseParameters();

			require(TokenType.RPAREN);
		}

		require(TokenType.COLON);

		Token type = consume();
		if ( type.mType != TokenType.TYPE ) {
			throw new ParseException("invalid token " + toString(type) + " found", type.mPosition);
		}

		require(TokenType.SEMICOLON);

		var oldScope = mCurrentScope;
		mCurrentScope = new SymbolTable(oldScope.mLevel + 1, name.mValue, oldScope);
		mCurrentScope.declare(Symbol new LocalSymbol("RESULT", type.mValue));

		var func = ScopeStatement new FunctionStatement(name.mValue, type.mValue);
		func.mParameters = declarations;

		// add function to current scope to allow recursive calls to it
		mCurrentScope.declare(Symbol new MethodSymbol(name.mValue, type.mValue, func));

		func.mBody = parseCompoundStatementWithDeclarations();

		mCurrentScope = oldScope;
		mCurrentScope.declare(Symbol new MethodSymbol(name.mValue, type.mValue, func));

		require(TokenType.SEMICOLON);

		return func;
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

	private MethodCallStatement parseMethodCall() modify throws {
		//print("parseMethodCall()");

		Token name = consume();

		var sym = mCurrentScope.lookup(name.mValue);
		if ( !(sym is MethodSymbol) ) {
			throw new ParseException("invalid symbol '" + name.mValue + "' detected", name.mPosition);
		}

		var params = new List<Expression>();

		while ( peek().mType == TokenType.LPAREN ) {
			params.push_back( expression() );

			if ( peek().mType == TokenType.COMMA ) {
				consume();	// consume ',' token
			}
		}

		var method = new MethodCallStatement(name.mValue, (MethodSymbol sym).mMethod);
		method.mParameters = params;

		return method;
	}

	private List<DeclarationStatement> parseParameters() modify throws {
		//print("parseParameters()");

		var declarations = new List<DeclarationStatement>();

		Token start = peek();
		while ( peek().mType == TokenType.IDENTIFIER ) {
			var declStmt = parseDeclarationStatement(false);
			declarations.push_back( declStmt );

			if ( mCurrentScope.lookup(declStmt.mName, true) ) {
				throw new ParseException("symbol '" + declStmt.mName + "' already exists", start.mPosition);
			}

			mCurrentScope.declare(Symbol new LocalSymbol(declStmt.mName, declStmt.mType, true));

			if ( peek().mType == TokenType.SEMICOLON ) {
				consume();	// consume ';' token
			}
		}

		return declarations;
	}

	private PrintStatement parsePrintStatement() modify throws {
		//print("parsePrintStatement()");

		require(TokenType.PRINT);

		return new PrintStatement( parseExpression() );
	}

	private ScopeStatement parseProcedure() modify throws {
		//print("parseProcedure()");

		require(TokenType.PROCEDURE);

		// name
		Token name = consume();
		if ( name.mType != TokenType.IDENTIFIER ) {
			throw new ParseException("invalid token " + toString(name) + " found", name.mPosition);
		}

		List<DeclarationStatement> declarations;

		Token token = peek();
		if ( token.mType == TokenType.LPAREN ) {
			require(TokenType.LPAREN);

			declarations = parseParameters();

			require(TokenType.RPAREN);
		}

		require(TokenType.SEMICOLON);

		var oldScope = mCurrentScope;
		mCurrentScope = new SymbolTable(oldScope.mLevel + 1, name.mValue, oldScope);

		var proc = ScopeStatement new ProcedureStatement(name.mValue);
		proc.mParameters = declarations;

		// add method symbol also to current scope to allow recursive method calls
		mCurrentScope.declare(Symbol new MethodSymbol(name.mValue, "void", proc));

		proc.mBody = parseCompoundStatementWithDeclarations();

		mCurrentScope = oldScope;
		mCurrentScope.declare(Symbol new MethodSymbol(name.mValue, "void", proc));

		require(TokenType.SEMICOLON);

		return proc;
	}

	private ProgramStatement parseProgram() modify throws {
		//print("parseProgram()");

		Token name = consume();
		if ( !name || name.mType != TokenType.IDENTIFIER ) {
			throw new ParseException("invalid PROGRAM statement found" + toString(name), name.mPosition);
		}

		require(TokenType.SEMICOLON);

		mCurrentScope = new SymbolTable(0, "global");

		Token token = peek();

		var uses = parseUsesStatement();
		var statements = parseCompoundStatementWithDeclarations();

		delete mCurrentScope;

		require(TokenType.DOT);

		return new ProgramStatement(name.mValue, uses, statements);
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
				stmt = Statement parseCompoundStatementWithDeclarations();
				break;
			}
			case TokenType.IDENTIFIER: {
				var sym = mCurrentScope.lookup(token.mValue);

				if ( sym && sym is LocalSymbol ) {
					stmt = Statement parseAssignStatement();
				}
				else if ( sym && sym is MethodSymbol ) {
					stmt = Statement parseMethodCall();
				}
				else {
					throw new ParseException("invalid symbol '" + token.mValue + "' detected", token.mPosition);
				}

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
				stmt = Statement parseCompoundStatementWithDeclarations();
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
			throw new ParseException("invalid UNIT statement found" + toString(name), name.mPosition);
		}

		require(TokenType.SEMICOLON);

		// push new scope
		mCurrentScope = new SymbolTable(0, "global");

		var uses = parseUsesStatement();

		require(TokenType.INTERFACE);

		require(TokenType.IMPLEMENTATION);

		var statements = parseCompoundStatementWithDeclarations();

		// pop scope
		delete mCurrentScope;

		require(TokenType.DOT);

		return new UnitStatement(name.mValue, uses, statements);
	}

	private UsesStatement parseUsesStatement() modify throws {
		//print("parseUsesStatement()");

		var uses = new UsesStatement();

		Token usesToken = peek();
		if ( usesToken && usesToken.mType == TokenType.USES ) {
			// consume uses token
			require(TokenType.USES);

			Token token;
			while ( (token = peek()) != null && token.mType == TokenType.IDENTIFIER ) {
				consume();	// consume unit name

				uses.mUnits.push_back( token.mValue );

				token = peek();
				if ( token && token.mType == TokenType.COMMA ) {
					consume();	// consume comma
					continue;
				}
				else if ( token && token.mType == TokenType.SEMICOLON ) {
					consume();	// consume semicolon
					break;
				}
				else {
					throw new ParseException("invalid USES statement", token.mPosition);
				}
			}
		}

		return uses;
	}

	private VariableDeclarationStatement parseVariableDeclarationStatement() modify throws {
		//print("parseVariableDeclarationStatement()");

		var stmt = new VariableDeclarationStatement();

		Token start = peek();
		if ( start && start.mType == TokenType.VAR ) {
			consume();	// consume VAR token

			while ( peek().mType == TokenType.IDENTIFIER ) {
				var declStmt = parseDeclarationStatement();
				stmt.mDeclarations.push_back( declStmt );

				if ( mCurrentScope.lookup(declStmt.mName, true) ) {
					throw new ParseException("symbol '" + declStmt.mName + "' already exists", start.mPosition);
				}

				mCurrentScope.declare(Symbol new LocalSymbol(declStmt.mName, declStmt.mType, false));
			}
		}

		return stmt;
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

	private string evaluateType(Expression left, Expression right) const {
		var leftToken = mTokenizer.getToken(left.mResultType);

		if ( leftToken && leftToken.mType == TokenType.TYPE ) {
			var rightToken = mTokenizer.getToken(right.mResultType);

			if ( rightToken && rightToken.mType == TokenType.TYPE ) {
				return leftToken.mValue;
			}
		}

		return "";
	}

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

		Expression left = parseTerm();

		Token op;
		while ( (op = peek()) != null && (op.mType == TokenType.MATH_MINUS || op.mType == TokenType.MATH_PLUS) ) {
			consume();

			Expression right = parseTerm();

			Expression exp = Expression new BinaryExpression(op, left, op.mValue, right, evaluateType(left, right));
			left = exp;
		}

		return left;
	}

	private Expression parseFactor() modify throws {
		//print("parseFactor()");

		Token token = peek();
		switch ( token.mType ) {
			case TokenType.BOOLEAN: {
				require(TokenType.BOOLEAN);
				return Expression new LiteralBooleanExpression(token, token.mValue == "TRUE");
			}
			case TokenType.IDENTIFIER: {
				return Expression parseIdentifier();
			}
			case TokenType.INTEGER: {
				require(TokenType.INTEGER);
				return Expression new LiteralIntegerExpression(token, int token.mValue);
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
			case TokenType.REAL: {
				require(TokenType.REAL);
				return Expression new LiteralRealExpression(token, float token.mValue);
			}
			case TokenType.STRING: {
				require(TokenType.STRING);
				return Expression new LiteralStringExpression(token, token.mValue);
			}
			default: {
				return Expression parseIdentifier();
			}
		}

		throw new ParseException("invalid factor expression found" + toString(token), token.mPosition);
	}

	private Expression parseTerm() modify throws {
		//print("parseTerm()");

		Expression left = parseFactor();

		Token op;
		while ( (op = peek()) != null &&
			(op.mType == TokenType.MATH_DIVIDE
			|| op.mType == TokenType.MATH_DIVIDE_INT
			|| op.mType == TokenType.MATH_MULTIPLY) ) {
			consume();

			Expression right = parseFactor();

			Expression exp = Expression new BinaryExpression(op, left, op.mValue, right, evaluateType(left, right));
			left = exp;
		}

		return left;
	}

	private Expression parseIdentifier() modify throws {
		//print("parseIdentifier()");

		Token token = consume();

		var sym = mCurrentScope.lookup(token.mValue);
		if ( !sym ) {
			throw new ParseException("unknown symbol '" + token.mValue + "' detected", token.mPosition);
		}

		if ( sym is LocalSymbol ) {
			if ( (LocalSymbol sym).mIsConst ) {
				return Expression new ConstantExpression(token, toUpper(token.mValue), sym.mType);
			}

			return Expression new VariableExpression(token, toUpper(token.mValue), sym.mType);
		}
		else if ( sym is MethodSymbol ) {
			// parse parameters
			var params = new List<Expression>();

			while ( peek().mType == TokenType.LPAREN ) {
				params.push_back( expression() );

				if ( peek().mType == TokenType.COMMA ) {
					consume();	// consume ',' token
				}
			}


			var method = new MethodExpression(token, (MethodSymbol sym).mMethod, sym.mType);
			method.mParameters = params;

			return Expression method;
		}

		throw new ParseException("invalid symbol '" + token.mValue + "' detected", token.mPosition);
	}

// Expression parsing
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// Helpers

	private Token consume() modify throws {
		try { return mTokenIterator.next(); }

		return Token null;
	}

	private Symbol getSymbol(string identifier) const throws {
		try { return mCurrentScope.lookup(identifier); }

		return Symbol null;
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


	private SymbolTable mCurrentScope;
	private Iterator<Token> mTokenIterator;
	private Tokenizer mTokenizer;
	private List<Token> mTokens;
}

