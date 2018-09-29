
// library imports
import System.CharacterIterator;
import System.Collections.Map;
import System.Collections.Set;
import System.IO.File;

// project imports
import Line;
import Scanner;


public object ParseException implements IException {
	public void Constructor(string msg, int line = 0, int column = 0) {
		mColumn = column;
		mLine = line;
		mMessage = msg;
	}

	public string what() const {
		return mMessage + " at Line " + mLine + ", " + mColumn;
	}

	private int mColumn;
	private int mLine;
	private string mMessage;
}

public object Parser {
	// Constants
	private String CHARS const;
	private String COMPARECHARS const;
	private String DELIMITERCHARS const;
	private String NUMBERS const;
	private String OPERATORCHARS const;
	private String WHITESPACES const;

	// Members
	private int mCurrentLine;
	private Set<string> mVariables;

	public void Constructor() {
		CHARS = new String("ABCDEFGHIJKLMNOPRSTUVWXYZabcdefghijklmnoprstuvwxyz");
		COMPARECHARS = new String("<>=");
		NUMBERS = new String("0123456789");
		OPERATORCHARS = new String("+-*/%");
		WHITESPACES = new String(" ");

		DELIMITERCHARS = new String( (string COMPARECHARS) + (string OPERATORCHARS) + (string WHITESPACES) );
	}

	public Map<int, Line> parseFile(string filename) modify {
		Scanner scanner = new Scanner(new System.IO.File(filename, System.IO.FileAccessMode.ReadOnly), LINEBREAK);

		// reset members
		mCurrentLine = 0;
		mVariables = new Set<string>();

		StringIterator it = scanner.getIterator();
		Map<int, Line> lines = new Map<int, Line>();
		Line previousLine;

		while ( it.hasNext() ) {
			// only parse non-empty lines
			if ( it.next() ) {
				Line line = parseLine(it.current());
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
		}

		return lines;
	}

	private Line parseLine(string content) modify throws {
		if ( strpos(content, 0) == "#" ) {
			return Line null;
		}

		// parse line number
		// {
		int idx = strfind(content, " ", 0);
		if ( !idx ) {
			throw new ParseException("invalid or missing line number: \"" + content + "\"");
		}

		string lineLabel = substr(content, 0, idx);
		if ( !isNumber(lineLabel) ) {
			throw new ParseException("invalid label \"" + lineLabel + "\"!");
		}
		// }

		mCurrentLine = int lineLabel;

		// parse statement
		// {
		CharacterIterator ci = new CharacterIterator(substr(content, idx + 1, strlen(content)));

		Statement statement = parseStatement(ci);
		if ( !statement ) {
			throw new ParseException("invalid keyword in line \"" + content + "\"");
		}

		skipWhitespaces(ci);

		Statement followingStatement = statement;
		if ( ci.hasNext() && ci.current() == ":" && bool followingStatement ) {
			ci.next();

			Statement stmt = parseStatement(ci);
			followingStatement.mFollowingStatement = Statement stmt;
			//followingStatement = Statement stmt;
		}
		// }

		return new Line(int lineLabel, statement);
	}

	private Statement parseStatement(CharacterIterator ci) modify throws {
		Statement result;

		switch ( parseWord(ci) ) {
			case "DIM": {
				result = parseDIM(ci);
				//print(result.toString());
				break;
			}
			case "END": {
				result = parseEND(ci);
				//print(result.toString());
				break;
			}
			case "FOR": {
				result = parseFOR(ci);
				//print(result.toString());
				break;
			}
			case "GOTO": {
				result = parseGOTO(ci);
				//print(result.toString());
				break;
			}
			case "IF": {
				result = parseIF(ci);
				//print(result.toString());
				break;
			}
			case "INPUT": {
				result = parseINPUT(ci);
				//print(result.toString());
				break;
			}
			case "LET": {
				result = parseLET(ci);
				//print(result.toString());
				break;
			}
			case "NEXT": {
				result = parseNEXT(ci);
				//print(result.toString());
				break;
			}
			case "PRINT": {
				result = parsePRINT(ci);
				//print(result.toString());
				break;
			}
			case "REM": {
				result = parseREM(ci);
				//print(result.toString());
				break;
			}
		}

		return result;
	}

	private Statement parseDIM(CharacterIterator ci) modify throws {
		if ( !ci.hasNext() ) {
			throw new ParseException("incomplete DIM!", mCurrentLine);
		}

		string variable = parseWord(ci);

		if ( mVariables.contains(variable) ) {
			throw new ParseException("Duplicate variable '" + variable + "' declared!", mCurrentLine);
		}
		mVariables.insert(variable);

		skipWhitespaces(ci);

		Expression exp;
		if ( ci.current() == "=" ) {
			ci.next();

			exp = expression(ci);
		}

		return Statement new DimStatement(variable, exp);
	}

	private Statement parseEND(CharacterIterator ci) throws {
		return Statement new EndStatement();
	}

	private Statement parseFOR(CharacterIterator ci) modify throws {
		if ( !ci.hasNext() ) {
			throw new ParseException("incomplete FOR!", mCurrentLine);
		}

		string variable = parseWord(ci);

		if ( !mVariables.contains(variable) ) {
			mVariables.insert(variable);
		}

		var varExp = new VariableExpression(variable);

		skipWhitespaces(ci);

		if ( ci.current() != "=" ) {
			throw "'=' expected!";
		}
		ci++;

		Expression initExp = expression(ci);

		string word;
		while ( ci.hasNext() && isCharacter(ci.current()) ) {
			word += ci.current();

			ci.next();
		}

		if ( word != "TO" ) {
			throw "'TO' expected but '" + word + "' found!";
		}

		Expression toExp = expression(ci); 

		Expression stepExp;
		if ( ci.hasNext() ) {
			word = "";

			while ( ci.hasNext() && isCharacter(ci.current()) ) {
				word += ci.current();

				ci.next();
			}

			if ( word != "STEP" ) {
				throw "'STEP' expected but '" + word + "' found!";
			}

			stepExp = expression(ci);
		}
		else {
			stepExp = expression("1");
		}

		return Statement new ForStatement(varExp,
						  initExp,
						  Expression new BinaryExpression(Expression varExp, "<", toExp),
						  Expression new BinaryExpression(Expression varExp, "+", stepExp));
	}

	private Statement parseGOTO(CharacterIterator ci) throws {
		if ( !ci.hasNext() ) {
			throw new ParseException("incomplete GOTO!", mCurrentLine);
		}

		return Statement new GotoStatement(int parseWord(ci));
	}

	private Statement parseIF(CharacterIterator ci) modify throws {
		if ( !ci.hasNext() ) {
			throw new ParseException("incomplete IF!", mCurrentLine);
		}

		Expression exp = expression(ci);

		string then;
		while ( ci.hasNext() && isCharacter(ci.current()) ) {
			then += ci.current();

			ci.next();
		}

		if ( then != "THEN" ) {
			throw "'THEN' expected but '" + then + "' found!";
		}

		return Statement new IfStatement(exp, parseStatement(ci));
	}

	private Statement parseINPUT(CharacterIterator ci) throws {
		if ( !ci.hasNext() ) {
			throw new ParseException("incomplete INPUT!", mCurrentLine);
		}

		string text;
		if ( ci.lookAHead() == "\"" ) {
			text = parseWord(ci);
		}

		return Statement new InputStatement(text, parseWord(ci));
	}

	private Statement parseLET(CharacterIterator ci) throws {
		if ( !ci.hasNext() ) {
			throw new ParseException("incomplete LET!", mCurrentLine);
		}

		string variable = parseWord(ci);

		skipWhitespaces(ci);

		if ( ci.current() != "=" ) {
			throw "LET: syntax error: missing '='";
		}
		ci.next();

		return Statement new LetStatement(variable, expression(ci));
	}

	private Statement parseNEXT(CharacterIterator ci) throws {
		if ( !ci.hasNext() ) {
			throw new ParseException("incomplete NEXT!", mCurrentLine);
		}

		string variable = parseWord(ci);

		return Statement new NextStatement(variable);
	}

	private Statement parsePRINT(CharacterIterator ci) throws {
		if ( !ci.hasNext() ) {
			throw new ParseException("incomplete LET!", mCurrentLine);
		}

		Expression exp = expression(ci);

		return Statement new PrintStatement(exp);
	}

	private Statement parseREM(CharacterIterator ci) throws {
		// ignore everything on this line
		return Statement new RemStatement(parseLine(ci));
	}


///////////////////////////////////////////////////////////
// Expression parsing

	private Expression expression(CharacterIterator ci) throws {
		var leftExp = expression(parseWord(ci));

		skipWhitespaces(ci);

		if ( ci.hasNext() && (isComparator(ci.current()) || isOperator(ci.current())) ) {
			var op = ci.current();

			if ( !ci.hasNext() ) {
				throw "invalid binary expression!";
			}

			ci.next();

			return Expression new BinaryExpression(leftExp, op, expression(ci));
		}

		return leftExp;
	}

	private Expression expression(string value) const throws {
		if ( isNumber(value) ) {
			return Expression new ConstNumberExpression(float value);
		}
		else if ( isVariable(value) ) {
			return Expression new VariableExpression(value);
		}
		else {
			return Expression new ConstStringExpression(value);
		}

		throw "invalid value '" + value + "' provided!";
	}


// Expression parsing
///////////////////////////////////////////////////////////

	private bool isCharacter(string value) const {
		return CHARS.Contains(value);
	}

	private bool isComparator(string value) const {
		return COMPARECHARS.Contains(value);
	}

	private bool isNumber(string value) const {
		if ( !value ) {
			return false;
		}

		var ci = new CharacterIterator(value);
		while ( ci.hasNext() ) {
			if ( !NUMBERS.Contains(ci.next()) ) {
				return false;
			}
		}

		return true;
	}

	private bool isOperator(string value) const {
		return OPERATORCHARS.Contains(value);
	}

	private bool isVariable(string value) const {
		if ( !value ) {
			return false;
		}

		return mVariables.contains(value);
	}

	private string parseLine(CharacterIterator ci) throws {
		string line;

		while ( ci.hasNext() ) {
			line += ci.next();
		}

		return line;
	}

	private string parseWord(CharacterIterator ci) const throws {
		bool isString;
		string word;

		while ( ci.hasNext() ) {
			string c = ci.next();

			if ( !isString && DELIMITERCHARS.Contains(c) ) {
				break;
			}

			if ( c == "\"" ) {
				isString = !isString;
				continue;
			}

			word += c;
		}

		return word;
	}

	private void skipWhitespaces(CharacterIterator ci) throws {
		while ( ci.hasNext() && WHITESPACES.Contains(ci.current()) ) {
			ci.next();
		}
	}
}

