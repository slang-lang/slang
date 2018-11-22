
// library imports
import System.Collections.List;
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
	public void Constructor() {
		// this is empty by intend
	}

	public void Destructor() {
		// this is empty by intend
	}

	public Statement parseFile(string filename) modify throws {
		var tokenizer = new Tokenizer();

		mTokens = tokenizer.parseFile(filename);
		mTokenIterator = mTokens.getIterator();

		print("");

		print("Building AST...");

		Statement statement;
		Token token;
		while ( (token = consume()) != null ) {
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
		}

		return statement;
	}

	private AssignmentStatement parseAssignStatement() modify throws {
		Token identifier = peek();

		require(TokenType.IDENTIFIER);

		var identifierExp = Expression new VariableExpression(identifier, identifier.mValue);

		require(TokenType.ASSIGN);

		var assignmentExp = expression();
		//print(toString(assignmentExp));
		if ( !assignmentExp ) {
			throw new ParseException("invalid ASSIGNMENT expression found", identifier.mPosition);
		}

		var assignmentStmt = new AssignmentStatement(
			identifierExp,
			assignmentExp
		);

		return assignmentStmt;
	}

	private CompoundStatement parseCompoundStatement() modify throws {
		print("parseCompoundStatement()");

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

	private PrintStatement parsePrintStatement() modify throws {
		print("parsePrintStatement()");

		require(TokenType.PRINT);

		return new PrintStatement( expression() );
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

	private Statement parseStatement() modify throws {
		print("parseStatement()");

		Statement stmt;

		Token token = peek();

		switch ( token.mType ) {
			case TokenType.BEGIN: {
				stmt = Statement parseCompoundStatement();
				break;
			}
			case TokenType.IDENTIFIER: {
				stmt = Statement parseAssignStatement();
				break;
			}
			case TokenType.PRINT: {
				stmt = Statement parsePrintStatement();
				break;
			}
			default: {
				throw new ParseException("invalid token found" + toString(token), token.mPosition);
			}
		}

		require(TokenType.SEMICOLON);

		return stmt;
	}

	private UnitStatement parseUnit() modify throws {
		//print("parseUnit()");

		Token name = consume();
		if ( !name && name.mType != TokenType.IDENTIFIER ) {
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


//////////////////////////////////////////////////////////////////////////////
// Expression parsing

	private Expression expression() modify throws {
		//print("expression()");

		Expression node = term();

		Token op;
		while ( (op = peek()) != null && (op.mType == TokenType.MINUS || op.mType == TokenType.PLUS) ) {
			consume();

			Expression exp = Expression new BinaryExpression(op, node, op.mValue, term());
			node = exp;
		}

		return node;
	}

	private Expression factor() modify throws {
		//print("factor()");

		Token token = peek();
		switch ( token.mType ) {
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
			case TokenType.MINUS: {
				require(TokenType.MINUS);
				return Expression new UnaryExpression(token, token.mValue, factor());	
			}
			case TokenType.PLUS: {
				require(TokenType.PLUS);
				return Expression new UnaryExpression(token, token.mValue, factor());	
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

	private Expression term() modify throws {
		//print("term()");

		Expression node = factor();

		Token op;
		while ( (op = peek()) != null && (op.mType == TokenType.DIVIDE || op.mType == TokenType.MULTIPLY) ) {
			consume();
			Expression exp = Expression new BinaryExpression(op, node, op.mValue, factor());
			node = exp;
		}

		return node;
	}

	private Expression parseIdentifier() modify throws {
		print("parseIdentifier()");

		Token token = consume();
		return Expression new VariableExpression(token, token.mValue);
	}

// Expression parsing
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// Helpers

	private Token consume() modify throws {
		try { return mTokenIterator.next(); }

		return Token null;
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


	private Iterator<Token> mTokenIterator;
	private List<Token> mTokens;
}

