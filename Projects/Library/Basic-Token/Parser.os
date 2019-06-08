
// library imports
import System.CharacterIterator;
import System.Collections.Map;
import System.Collections.Set;
import System.IO.File;

// project imports
import Line;
import Token;
import Tokenizer;


public object ParseException const implements IException {
	public void Constructor(string msg, int line = 0, int column = 0) {
		mColumn = column;
		mLine = line;
		mMessage = msg;
	}

	public string what() const {
		return mMessage + mLine ? (" at Line " + mLine + ", " + mColumn) : "";
	}

	private int mColumn const;
	private int mLine const;
	private string mMessage const;
}

public object Parser {
	public Map<int, Line> parseFile(string filename, bool debug = false) modify {
		mTokenizer = new Tokenizer();
		mTokens = mTokenizer.parseFile(filename, debug);
		mTokenIterator = mTokens.getIterator();

		if ( debug ) {
			print("Building AST for \"" + filename + "\"...");
		}

		// reset members
		mCurrentLine = 0;
		mVariables = new Set<string>();

		Map<int, Line> lines = new Map<int, Line>();
		Line previousLine;

		while ( peek() ) {
			Line line = parseLine();
			if ( !line ) {
				// ignore invalid lines (mostly shebangs ;-)
				continue;
			}

			lines.insert(line.mLineNumber, line);

			if ( previousLine ) {
				previousLine.nextLine(line.mLineNumber);
			}

			previousLine = line;
		}

		mCurrentLine = 0;

		if ( debug ) {
			print("Done building AST.");
		}

		return lines;
	}

	public Line parseLine() modify throws {
		// parse line number
		// {
		Token lineNumber = consume();
		if ( lineNumber.mType != TokenType.INTEGER ) {
			throw new ParseException("invalid or missing line number: \"" + lineNumber.mValue + "\"");
		}
		// }

		mCurrentLine = int lineNumber.mValue;

		// parse statement
		// {
		Statement statement = parseStatement();
		if ( !statement ) {
			throw new ParseException("invalid keyword in line \"" + lineNumber.mValue + "\"");
		}

		Statement nextStatement = statement;
		while ( peek().mType == TokenType.COLON ) {
			consume();	// consume ':' token

			nextStatement.mFollowingStatement = Statement parseStatement();
			nextStatement = nextStatement.mFollowingStatement;
		}
		// }

		if ( peek().mType == TokenType.LINEBREAK ) {
			consume();	// consume linebreak
		}

		return new Line(int lineNumber.mValue, statement);
	}

	public Statement parseStatement() modify throws {
		Statement result;

		Token token = peek();
		switch ( (token = peek()).mType ) {
			case TokenType.LINEBREAK: {
				consume();	// consume linebreak
				return result;
			}
			case TokenType.DIM: {
				result = Statement parseDIM();
				break;
			}
			case TokenType.END: {
				result = Statement parseEND();
				break;
			}
			case TokenType.FOR: {
				result = Statement parseFOR();
				break;
			}
			case TokenType.GOTO: {
				result = Statement parseGOTO();
				break;
			}
			case TokenType.IF: {
				result = Statement parseIF();
				break;
			}
			case TokenType.INPUT: {
				result = Statement parseINPUT();
				break;
			}
			case TokenType.LET: {
				result = Statement parseLET();
				break;
			}
			case TokenType.NEXT: {
				result = Statement parseNEXT();
				break;
			}
			case TokenType.PRINT: {
				result = Statement parsePRINT();
				break;
			}
			case TokenType.REM: {
				result = Statement parseREM();
				break;
			}
			default: {
				throw "unknown token '" + toString(token) + "' found";
			}
		}

		return result;
	}

	private DimStatement parseDIM() modify throws {
		require(TokenType.DIM);

		Token variable = consume();
		if ( !variable || variable.mType != TokenType.IDENTIFIER ) {
			throw new ParseException("invalid token '" + toString(variable) + "' found");
		}

		if ( mVariables.contains(variable.mValue) ) {
			throw new ParseException("Duplicate variable '" + toString(variable) + "' declared!", mCurrentLine);
		}
		mVariables.insert(variable.mValue);

		Expression exp;
		if ( peek().mType == TokenType.ASSIGN ) {
			consume();	// consume '=' token

			exp = expression();
		}

		var stmt = new DimStatement(variable.mValue, exp);
		consume();
		return stmt;
	}

	private EndStatement parseEND() modify throws {
		require(TokenType.END);

		return new EndStatement();
	}

	private ForStatement parseFOR() modify throws {
		require(TokenType.FOR);

		Token variable = consume();
		if ( !variable || variable.mType != TokenType.IDENTIFIER ) {
			throw new ParseException("invalid token '" + toString(variable) + "' found");
		}

		if ( !mVariables.contains(variable.mValue) ) {
			mVariables.insert(variable.mValue);
		}

		var varExp = new VariableExpression(variable.mValue);

		require(TokenType.ASSIGN);

		Expression initExp = expression();

		require(TokenType.TO);

		Expression toExp = expression(); 

		Expression stepExp;
		if ( peek().mType == TokenType.STEP ) {
			consume();	// consume STEP token

			stepExp = expression();
		}

		return new ForStatement(varExp, initExp, Expression new BooleanBinaryExpression(Expression varExp, "<", toExp), Expression new BinaryExpression(Expression varExp, "+", stepExp));
	}

	private GotoStatement parseGOTO() modify throws {
		require(TokenType.GOTO);

		Token lineNumber = consume();
		if ( !lineNumber || lineNumber.mType != TokenType.INTEGER ) {
			throw "invalid token '" + toString(lineNumber) + "'";
		}

		return new GotoStatement( cast<int>(lineNumber.mValue) );
	}

	private IfStatement parseIF() modify throws {
		require(TokenType.IF);

		Expression exp = expression();

		require(TokenType.THEN);

		return new IfStatement(exp, parseStatement());
	}

	private InputStatement parseINPUT() modify throws {
		require(TokenType.INPUT);

		Token text;
		if ( peek().mType == TokenType.STRING ) {
			text = consume();
		}

		Token variable = consume();
		if ( !variable || variable.mType != TokenType.IDENTIFIER ) {
			throw "invalid identifier '" + toString(variable) + "'";
		}

		return new InputStatement(text ? text.mValue : "", variable.mValue);
	}

	private LetStatement parseLET() modify throws {
		require(TokenType.LET);

		Token variable = consume();
		if ( !variable || variable.mType != TokenType.IDENTIFIER ) {
			throw "invalid identifier '" + toString(variable) + "'";
		}

		require(TokenType.ASSIGN);

		return new LetStatement(variable.mValue, expression());
	}

	private NextStatement parseNEXT() modify throws {
		require(TokenType.NEXT);

		Token variable = consume();
		if ( !variable || variable.mType != TokenType.IDENTIFIER ) {
			throw "invalid identifier '" + toString(variable) + "'";
		}

		return new NextStatement(variable.mValue);
	}

	private PrintStatement parsePRINT() modify throws {
		require(TokenType.PRINT);

		return new PrintStatement(expression());
	}

	private RemStatement parseREM() modify throws {
		require(TokenType.REM);

		// ignore everything on this line
		string comment;

		Token token;
		while ( (token = consume()).mType != TokenType.LINEBREAK ) {
			comment += token.mValue + " ";
		}

		return new RemStatement(comment);
	}


///////////////////////////////////////////////////////////
// Expression parsing

	private Expression expression() modify throws {
		//print("expression()");

		Expression left = parseCondition();

		Token op;
		while ( (op = peek()) != null &&
				(op.mType == TokenType.AND || op.mType == TokenType.OR) ) {
			consume();

			Expression right = parseCondition();

			Expression exp = Expression new BooleanBinaryExpression(left, op.mValue, right);
			left = exp;
		}

		return left;
	}

	private Expression parseCondition() modify throws {
		//print("parseCondition()");

		Expression left = parseExpression();

		Token op;
		while ( (op = peek()) != null && isComperator(op) ) {
			consume();

			Expression right = parseExpression();

			Expression exp = Expression new BooleanBinaryExpression(left, op.mValue, right);
			left = exp;
		}

		return left;
	}

	private Expression parseExpression() modify throws {
		//print("parseExpression()");

		Expression left = parseFactor();

		Token op;
		while ( (op = peek()) != null &&
				(op.mType == TokenType.MATH_MINUS || op.mType == TokenType.MATH_PLUS) ) {
			consume();

			Expression right = parseFactor();

			Expression exp = Expression new BinaryExpression(left, op.mValue, right);
			left = exp;
		}

		return left;
	}

	private Expression parseFactor() modify throws {
		//print("parseFactor()");

		Expression left = parseTerm();

		Token op;
		while ( (op = peek()) != null &&
				(op.mType == TokenType.MATH_DIVIDE || op.mType == TokenType.MATH_MULTIPLY) ) {
			consume();

			Expression right = parseTerm();

			Expression exp = Expression new BinaryExpression(left, op.mValue, right);
			left = exp;
		}

		return left;
	}

	private Expression parseTerm() modify throws {
		//print("parseTerm()");

		Token token = peek();
		switch ( token.mType ) {
			case TokenType.BOOLEAN: {
				require(TokenType.BOOLEAN);
				return Expression new ConstNumberExpression( cast<float>(token.mValue == "TRUE") );
			}
			case TokenType.IDENTIFIER: {
				return Expression new VariableExpression(consume().mValue);
			}
			case TokenType.INTEGER: {
				require(TokenType.INTEGER);
				return Expression new ConstNumberExpression( cast<float>(token.mValue) );
			}
			case TokenType.LPAREN: {
				require(TokenType.LPAREN);
				Expression exp = expression();
				require(TokenType.RPAREN);
				return exp;
			}
			case TokenType.MATH_MINUS: {
				require(TokenType.MATH_MINUS);
				return Expression new UnaryExpression("-", Expression parseTerm());
			}
			case TokenType.MATH_PLUS: {
				require(TokenType.MATH_PLUS);
				return Expression new UnaryExpression("+", Expression parseTerm());
			}
			case TokenType.REAL: {
				require(TokenType.REAL);
				return Expression new ConstNumberExpression( cast<float>(token.mValue) );
			}
			case TokenType.STRING: {
				require(TokenType.STRING);
				return Expression new ConstStringExpression(token.mValue);
			}
			default: {
				return Expression new VariableExpression(token.mValue);
			}
		}

		throw new ParseException("invalid factor expression found" + toString(token));
	}

// Expression parsing
///////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Helpers

	private Token consume() modify throws {
		try { return mTokenIterator.next(); }

		return Token null;
	}

	private bool isComperator(Token token) const {
		switch ( token.mType ) {
			case TokenType.ASSIGN:			{ return true; }
			case TokenType.GREATER:			{ return true; }
			case TokenType.GREATER_EQUAL:	{ return true; }
			case TokenType.LESS:			{ return true; }
			case TokenType.LESS_EQUAL:		{ return true; }
			case TokenType.UNEQUAL:			{ return true; }
			default:						{ return false; }
		}

		return false;
	}

	private bool isVariable(string value) const {
		if ( !value ) {
			return false;
		}

		return mVariables.contains(value);
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
			throw new ParseException(TokenToString(tokenType) + " expected but " + toString(token) + " found");
		}
	}

// Helpers
//////////////////////////////////////////////////////////////////////////////

	// Members
	private int mCurrentLine;
	private Iterator<Token> mTokenIterator;
	private Tokenizer mTokenizer;
	private List<Token> mTokens;
	private Set<string> mVariables;
}

