
// library imports
import System.Collections.List;
import System.Collections.Map;
import System.IO.File;

// project imports
import Expressions;
import Scope;
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
		mTokenizer = new Tokenizer();
		mTokens = mTokenizer.parseFile(filename, debug);
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

		Token identifier = consume();

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

		var identifierExp = Expression new VariableExpression(identifier, (LocalSymbol sym).mStackIndex, toUpper(identifier.mValue), (LocalSymbol sym).mType);

		require(TokenType.ASSIGN);

		var assignmentExp = expression();
		if ( !assignmentExp ) {
			throw new ParseException("invalid ASSIGNMENT expression found", identifier.mPosition);
		}

		return new AssignmentStatement(identifierExp, assignmentExp);
	}

	private BreakStatement parseBreakStatement() modify throws {
		//print("parseBreakStatement()");

		if ( !mCurrentScope.isBreakAllowed() ) {
			throw new ParseException("break not allowed here", peek().mPosition);
		}

		require(TokenType.BREAK);

		return new BreakStatement();
	}

	private CasePart parseCasePart(string caseType) modify throws {
		//print("parseCasePart()");

		var casePart = new CasePart(caseType);

		Token token = peek();
		for ( ; ; ) {
			var exp = expression();

			if ( exp.mResultType != caseType ) {
				throw new ParseException("expression type '" + exp.mResultType + "' does not match case-type '" + caseType + "'", token.mPosition);
			}
			if ( !(exp is LiteralExpression) ) {
				throw new ParseException("literal expression expected but " + typeid(exp) + " detected", token.mPosition);
			}

			casePart.mExpressions.push_back(exp);

			if ( peek().mType != TokenType.COMMA ) {
				break;
			}

			require(TokenType.COMMA);
		}

		require(TokenType.COLON);

		casePart.mStatement = parseStatement();

		return casePart;
	}

	private CaseStatement parseCaseStatement() modify throws {
		//print("parseCaseStatement()");

		require(TokenType.CASE);

		var caseExp = expression();

		require(TokenType.OF);

		var caseStmt = new CaseStatement(caseExp);

		Token token;
		for ( ; ; ) {
			var casePart = parseCasePart(caseExp.mResultType);

			if ( casePart.mType != caseExp.mResultType ) {
				throw new ParseException("expression type '" + casePart.mType + "' does not match case-type '" + caseExp.mResultType + "'", token.mPosition);
			}

			caseStmt.mCaseParts.push_back(casePart);

			if ( (token = peek()) != null && (token.mType == TokenType.ELSE || token.mType == TokenType.END) ) {
				break;
			}
		}

		if ( token.mType == TokenType.ELSE ) {
			consume();	// consume ELSE token

			caseStmt.mElseStatement = parseStatement();
		}

		require(TokenType.END);

		return caseStmt;
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

		return new CompoundStatement( statements );
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
				stmt = ScopeStatement parseFunction();
			}
			else if ( token.mType == TokenType.PROCEDURE ) {
				stmt = ScopeStatement parseProcedure();
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
				var declStmt = parseDeclarationStatement(true, true);
				stmt.mDeclarations.push_back( declStmt );

				if ( mCurrentScope.lookup(declStmt.mName, true) ) {
					throw new ParseException("symbol '" + declStmt.mName + "' already exists", start.mPosition);
				}

				mCurrentScope.declare(Symbol new LocalSymbol(declStmt.mName, mCurrentScope.size(), declStmt.mType, true));
			}
		}

		return stmt;
	}

	private ContinueStatement parseContinueStatement() modify throws {
		//print("parseContinueStatement()");

		if ( !mCurrentScope.isContinueAllowed() ) {
			throw new ParseException("continue not allowed here", peek().mPosition);
		}

		require(TokenType.CONTINUE);

		return new ContinueStatement();
	}

	private DeclarationStatement parseDeclarationStatement(bool isConst, bool requireSemicolon) modify throws {
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
			value,
			isConst
		);
	}

	private List<DeclarationStatement> parseFormalParameters() modify throws {
		//print("parseFormalParameters()");

		var declarations = new List<DeclarationStatement>();

		Token start = peek();
		if ( start.mType == TokenType.LPAREN ) {
			require(TokenType.LPAREN);

			while ( peek().mType == TokenType.IDENTIFIER ) {
				var declStmt = parseDeclarationStatement(false, false);
				declarations.push_back( declStmt );

				if ( mCurrentScope.lookup(declStmt.mName, true) ) {
					throw new ParseException("symbol '" + declStmt.mName + "' already exists", start.mPosition);
				}

				mCurrentScope.declare(Symbol new LocalSymbol(declStmt.mName, mCurrentScope.size(), declStmt.mType, false));

				if ( peek().mType == TokenType.SEMICOLON ) {
					consume();	// consume ';' token
				}
			}

			require(TokenType.RPAREN);
		}

		return declarations;
	}

	private ExitStatement parseExitStatement() modify throws {
		//print("parseExitStatement()");

		require(TokenType.EXIT);

		Expression exp;
		if ( peek().mType == TokenType.LPAREN ) {
			consume();	// consume ( token

			if ( !mCurrentScope.lookup("RESULT", true) ) {
				// no RESULT symbol found => this is obviously no function
				throw new ParseException("EXIT with return value can only be used in functions", peek().mPosition);
			}

			exp = expression();

			require(TokenType.RPAREN);
		}

		return new ExitStatement(exp);
	}

	private ForStatement parseForStatement() modify throws {
		//print("parseForStatement()");

		Token token = consume();

		var varExp = expression();
		if ( !(varExp is VariableExpression) ) {
			throw new ParseException("variable expected", token.mPosition);
		}
		if ( varExp.mResultType != "INTEGER" ) {
			throw new ParseException("INTEGER type required", token.mPosition);
		}

		require(TokenType.ASSIGN);

		var startExp = expression();

		require(TokenType.TO);

		var targetExp = expression();

		require(TokenType.DO);

		Expression stepExp;
		if ( peek().mType == TokenType.STEP ) {
			require(TokenType.STEP);

			stepExp = expression();
		}
		else {
			stepExp = Expression new LiteralIntegerExpression(token, 1);
		}

		mCurrentScope.pushProperty(true);

		var body = parseStatement(false);

		mCurrentScope.popProperty();

		return new ForStatement(VariableExpression varExp,
					startExp,
					Expression new BooleanBinaryExpression(token, varExp, "<=", targetExp),
					Expression new BinaryExpression(token, varExp, "+", stepExp, varExp.mResultType),
					body);
	}

	private FunctionStatement parseFunction() modify throws {
		//print("parseFunction()");

		require(TokenType.FUNCTION);

		// name
		Token name = consume();
		if ( name.mType != TokenType.IDENTIFIER ) {
			throw new ParseException("invalid token " + toString(name) + " found", name.mPosition);
		}

		// store current scope and push a new one
		var oldScope = mCurrentScope;
		mCurrentScope = new Scope(name.mValue, oldScope);

		var params = parseFormalParameters();

		require(TokenType.COLON);

		Token type = consume();
		if ( type.mType != TokenType.TYPE ) {
			throw new ParseException("invalid token " + toString(type) + " found", type.mPosition);
		}

		require(TokenType.SEMICOLON);

		var func = new FunctionStatement(name.mValue, type.mValue);
		func.mParameters = params;

		// add local symbol "result" to store function return value
		mCurrentScope.declare(Symbol new LocalSymbol("RESULT", mCurrentScope.size(), type.mValue));
		// add function to current scope to allow recursive calls to it
		mCurrentScope.declare(Symbol new MethodSymbol(name.mValue, mCurrentScope.size(), type.mValue, ScopeStatement func));

		func.mBody = parseCompoundStatementWithDeclarations();

		// restore previous scope
		mCurrentScope = oldScope;
		mCurrentScope.declare(Symbol new MethodSymbol(name.mValue, mCurrentScope.size(), type.mValue, ScopeStatement func));

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

		var method = new MethodCallStatement(name.mValue, (MethodSymbol sym).mMethod);
		method.mParameters = parseMethodParameters(name, MethodSymbol sym);

		return method;
	}

	private List<Expression> parseMethodParameters(Token name, MethodSymbol symbol) modify throws {
		//print("parseMethodParameters()");

		var formalParams = symbol.mMethod.mParameters;
		var params = new List<Expression>();
		var formalIt = formalParams.getIterator();

		if ( peek().mType == TokenType.LPAREN ) {
			require(TokenType.LPAREN);

			Expression exp;
			while ( (exp = expression()) != null ) {
				if ( !formalIt.hasNext() ) {
					throw new ParseException("provided more parameters than expected for method '" + name.mValue + "'", name.mPosition);
				}

				var decl = formalIt.next();
				if ( decl.mType != exp.mResultType ) {
					throw new ParseException("provided wrong type '" + exp.mResultType + "' instead of '" + decl.mType + "' for method '" + name.mValue + "'", name.mPosition);
				}

				params.push_back( exp );

				if ( peek().mType == TokenType.COMMA ) {
					consume();	// consume ',' token
					continue;
				}

				break;
			}

			require(TokenType.RPAREN);
		}

		if ( params.size() != formalParams.size() ) {
			throw new ParseException("wrong number of parameters provided for method '" + name.mValue + "'", name.mPosition);
		}

		return params;
	}

	private ProcedureStatement parseProcedure() modify throws {
		//print("parseProcedure()");

		require(TokenType.PROCEDURE);

		// name
		Token name = consume();
		if ( name.mType != TokenType.IDENTIFIER ) {
			throw new ParseException("invalid token " + toString(name) + " found", name.mPosition);
		}

		// store current scope and push a new one
		var oldScope = mCurrentScope;
		mCurrentScope = new Scope(name.mValue, oldScope);

		var params = parseFormalParameters();

		require(TokenType.SEMICOLON);

		var proc = new ProcedureStatement(name.mValue);
		proc.mParameters = params;

		// add method symbol also to current scope to allow recursive method calls
		mCurrentScope.declare(Symbol new MethodSymbol(name.mValue, mCurrentScope.size(), "void", ScopeStatement proc));

		proc.mBody = parseCompoundStatementWithDeclarations();

		// restore previous scope
		mCurrentScope = oldScope;
		mCurrentScope.declare(Symbol new MethodSymbol(name.mValue, mCurrentScope.size(), "void", ScopeStatement proc));

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

		mCurrentScope = new Scope("global");

		Token token = peek();

		var uses = parseUsesStatement();
		var statements = parseCompoundStatementWithDeclarations();

		delete mCurrentScope;

		require(TokenType.DOT);

		return new ProgramStatement(name.mValue, uses, statements);
	}

	private ReadlineStatement parseReadlineStatement() modify throws {
		//print("parseReadlineStatement()");

		Token token = consume();

		require(TokenType.LPAREN);

		var varExp = expression();
		if ( !(varExp is VariableExpression) ) {
			throw new ParseException("variable expected", token.mPosition);
		}

		require(TokenType.RPAREN);

		return new ReadlineStatement(VariableExpression varExp);
	}

	private RepeatStatement parseRepeatStatement() modify throws {
		//print("parseRepeatStatement()");

		Token token = consume();
		if ( !token || token.mType != TokenType.REPEAT ) {
			throw new ParseException("invalid REPEAT statement found" + toString(token), token.mPosition);
		}

		mCurrentScope.pushProperty(true);

		var statements = new List<Statement>();
		while ( (token = peek()) != null && token.mType != TokenType.UNTIL ) {
			statements.push_back( parseStatement() );
		}

		mCurrentScope.popProperty();

		require(TokenType.UNTIL);

		var conditionExp = expression();

		return new RepeatStatement(statements, conditionExp);
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
			case TokenType.BREAK: {
				stmt = Statement parseBreakStatement();
				break;
			}
			case TokenType.CASE: {
				stmt = Statement parseCaseStatement();
				break;
			}
			case TokenType.CONST: {
				stmt = Statement parseCompoundStatementWithDeclarations();
				break;
			}
			case TokenType.CONTINUE: {
				stmt = Statement parseContinueStatement();
				break;
			}
			case TokenType.EXIT: {
				stmt = Statement parseExitStatement();
				break;
			}
			case TokenType.FOR: {
				stmt = Statement parseForStatement();
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
			case TokenType.READLN: {
				stmt = Statement parseReadlineStatement();
				break;
			}
			case TokenType.REPEAT: {
				stmt = Statement parseRepeatStatement();
				break;
			}
			case TokenType.SEMICOLON: {
				// nothing to do here
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
			case TokenType.WRITE: {
				stmt = Statement parseWriteStatement(false);
				break;
			}
			case TokenType.WRITELN: {
				stmt = Statement parseWriteStatement(true);
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
		mCurrentScope = new Scope(name.mValue);

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
				var declStmt = parseDeclarationStatement(false, true);
				stmt.mDeclarations.push_back( declStmt );

				if ( mCurrentScope.lookup(declStmt.mName, true) ) {
					throw new ParseException("symbol '" + declStmt.mName + "' already exists", start.mPosition);
				}

				mCurrentScope.declare(Symbol new LocalSymbol(declStmt.mName, mCurrentScope.size(), declStmt.mType, false));
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

		mCurrentScope.pushProperty(true);

		var body = parseStatement(false);

		mCurrentScope.popProperty();

		return new WhileStatement(condition, body);
	}

	private WriteStatement parseWriteStatement(bool lineBreak) modify throws {
		//print("parseWriteStatement()");

		if ( lineBreak ) {
			require(TokenType.WRITELN);
		}
		else {
			require(TokenType.WRITE);
		}

		return new WriteStatement( parseExpression(), lineBreak );
	}


//////////////////////////////////////////////////////////////////////////////
// Expression parsing

	private string evaluateType(Expression left, Expression right) const {
		var leftToken const = mTokenizer.getToken(left.mResultType);

		if ( leftToken && leftToken.mType == TokenType.TYPE ) {
			var rightToken const = mTokenizer.getToken(right.mResultType);

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
		while ( (op = peek()) != null &&
				(op.mType == TokenType.AND || op.mType == TokenType.OR) ) {
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

		Expression left = parseFactor();

		Token op;
		while ( (op = peek()) != null &&
				(op.mType == TokenType.MATH_MINUS || op.mType == TokenType.MATH_PLUS) ) {
			consume();

			Expression right = parseFactor();

			Expression exp = Expression new BinaryExpression(op, left, op.mValue, right, evaluateType(left, right));
			left = exp;
		}

		return left;
	}

	private Expression parseFactor() modify throws {
		//print("parseFactor()");

		Expression left = parseTerm();

		Token op;
		while ( (op = peek()) != null &&
				(op.mType == TokenType.MATH_DIVIDE || op.mType == TokenType.MATH_DIVIDE_INT || op.mType == TokenType.MATH_MULTIPLY) ) {
			consume();

			Expression right = parseTerm();

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
				return Expression new ConstantExpression(token, (LocalSymbol sym).mStackIndex, toUpper(token.mValue), sym.mType);
			}

			return Expression new VariableExpression(token, (LocalSymbol sym).mStackIndex, toUpper(token.mValue), sym.mType);
		}
		else if ( sym is MethodSymbol ) {
			var method = new MethodExpression(token, (MethodSymbol sym).mStackIndex, (MethodSymbol sym).mMethod, sym.mType);
			method.mParameters = parseMethodParameters(token, MethodSymbol sym);

			return Expression method;
		}

		throw new ParseException("invalid symbol '" + token.mValue + "' detected", token.mPosition);
	}

	private Expression parseTerm() modify throws {
		//print("parseTerm()");

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
				return Expression new LiteralIntegerExpression(token, cast<int>( token.mValue ) );
			}
			case TokenType.LPAREN: {
				require(TokenType.LPAREN);
				Expression node = expression();
				require(TokenType.RPAREN);

				return node;
			}
			case TokenType.MATH_MINUS: {
				require(TokenType.MATH_MINUS);
				return Expression new UnaryExpression(token, token.mValue, parseTerm());	
			}
			case TokenType.MATH_PLUS: {
				require(TokenType.MATH_PLUS);
				return Expression new UnaryExpression(token, token.mValue, parseTerm());	
			}
			case TokenType.REAL: {
				require(TokenType.REAL);
				return Expression new LiteralRealExpression(token, cast<float>( token.mValue ) );
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


	private Scope mCurrentScope;
	private Iterator<Token> mTokenIterator;
	private Tokenizer mTokenizer;
	private List<Token> mTokens;
}

