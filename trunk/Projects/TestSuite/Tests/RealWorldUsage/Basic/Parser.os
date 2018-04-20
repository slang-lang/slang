
// library imports
import System.CharacterIterator;
import System.Collections.Map;
import System.IO.File;

// project imports
import Line;
import Scanner;


public object Parser {
	private String CHARS const;
	private string COMPARECHARS const = "<>=";
	private String DELIMITERCHARS const;
	private String NUMBERS const;
	private string OPERATORCHARS const = "+-*/%";
	private String WHITESPACES const;

	public void Constructor() {
		CHARS = new String("ABCDEFGHIJKLMNOPRSTUVWXYZabcdefghijklmnoprstuvwxyz");
		NUMBERS = new String("0123456789");
		WHITESPACES = new String(" ");

		DELIMITERCHARS = new String(COMPARECHARS + OPERATORCHARS + string WHITESPACES);
	}

	public Map<int, Line> parseFile(string filename) modify {
		Scanner scanner = new Scanner(new System.IO.File(filename, "r"), ascii(10));

		print("Parsing file '" + filename + "'...");

		StringIterator it = scanner.getIterator();
		Map<int, Line> lines = new Map<int, Line>();
		Line previousLine;

		while ( it.hasNext() ) {
			it++;

			if ( it.current() ) {
				print(string it);

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

		print("Done parsing.");
		print("");

		return lines;
	}

	private Line parseLine(string content) throws {
		if ( strpos(content, 0) == "#" ) {
			return Line null;
		}

		// parse line number
		// {
		int idx = strfind(content, " ", 0);
		if ( !idx ) {
			throw new Exception("invalid or missing line number: \"" + content + "\"");
		}

		string lineLabel = substr(content, 0, idx);
		// }

		// parse statement
		// {
		CharacterIterator ci = new CharacterIterator(substr(content, idx + 1, strlen(content)));

		Statement statement = parseStatement(ci);
		if ( !statement ) {
			throw new Exception("invalid keyword in line \"" + content + "\"");
		}
		// }

		return new Line(int lineLabel, statement);
	}

	private Statement parseStatement(CharacterIterator ci) throws {
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
			case "GOTO": {
				result = parseGOTO(ci);
				//print(result.toString());
				break;
			}
			case "IF": {
				result = parseIF(ci);
				print(result.toString());
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

	private Statement parseDIM(CharacterIterator ci) throws {
		if ( !ci.hasNext() ) {
			throw new Exception("incomplete DIM!");
		}

		string variable = parseWord(ci);
		Expression exp;

		skipWhitespaces(ci);

		if ( ci.current() == "=" ) {
			ci.next();

			exp = expression(ci);
		}

		return Statement new DimStatement(variable, exp);
	}

	private Statement parseEND(CharacterIterator ci) throws {
		return Statement new EndStatement();
	}

	private Statement parseGOTO(CharacterIterator ci) throws {
		if ( !ci.hasNext() ) {
			throw new Exception("incomplete GOTO!");
		}

		return Statement new GotoStatement(int parseWord(ci));
	}

	private Statement parseIF(CharacterIterator ci) throws {
		if ( !ci.hasNext() ) {
			throw new Exception("incomplete IF!");
		}

		Expression exp = expression(ci);

		string then;
		while ( ci.hasNext() && isCharacter(ci.current()) ) {
			then += ci.current();

			ci.next();
		}

		if ( then != "THEN" ) {
			throw "'THEN' excpected but '" + then + "' found!";
		}

		return Statement new IfStatement(exp, parseStatement(ci));
	}

	private Statement parseINPUT(CharacterIterator ci) throws {
		if ( !ci.hasNext() ) {
			throw new Exception("incomplete INPUT!");
		}

		string text;
		if ( ci.lookAHead() == "\"" ) {
			text = parseWord(ci);
		}

		return Statement new InputStatement(text, parseWord(ci));
	}

	private Statement parseLET(CharacterIterator ci) throws {
		if ( !ci.hasNext() ) {
			throw new Exception("incomplete LET!");
		}

		string variable = parseWord(ci);

		skipWhitespaces(ci);

		if ( ci.current() != "=" ) {
			throw "LET: syntax error: missing '='";
		}
		ci.next();

		return Statement new LetStatement(variable, expression(ci));
	}

	private Statement parsePRINT(CharacterIterator ci) throws {
		if ( !ci.hasNext() ) {
			throw new Exception("incomplete LET!");
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

			var rightExp = expression(ci);

			var binaryExp = new BinaryExpression(op);
			binaryExp.mLeft = leftExp;
			binaryExp.mRight = rightExp;

			return Expression binaryExp;
		}

		return leftExp;
	}

	private Expression expression(string value) const throws {
		if ( isNumber(new String(value)) ) {
			return Expression new ConstNumberExpression(float value);
		}
		else if ( isVariable(new String(value)) ) {
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
		return strfind(COMPARECHARS, value, 0) >= 0;
	}

	private bool isNumber(String value) const {
		if ( !value ) {
			return false;
		}

		foreach ( string s : value ) {
			if ( !NUMBERS.Contains(s) ) {
				return false;
			}
		}

		return true;
	}

	private bool isOperator(string value) const {
		return strfind(OPERATORCHARS, value, 0) >= 0;
	}

	private bool isVariable(String value) const {
		if ( !value ) {
			return false;
		}

		foreach ( string s : value ) {
			if ( !CHARS.Contains(s) ) {
				return false;
			}
		}

		return true;
	}

	private string parseLine(CharacterIterator ci) throws {
		string line;

		while ( ci.hasNext() ) {
			ci++;
			string c = ci.current();

			line += c;
		}

		return line;
	}

	private string parseWord(CharacterIterator ci) throws {
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

	private void skipWhitespaces(CharacterIterator ci) const throws {
		while ( ci.hasNext() && WHITESPACES.Contains(ci.current()) ) {
			ci.next();
		}
	}
}

