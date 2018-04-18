#!/usr/local/bin/oscript

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
	private string OPERATORCHARS const = "+-*/";
	private String WHITESPACES const;

	public void Constructor() {
		CHARS = new String("ABCDEFGHIJKLMNOPRSTUVWXYZ");
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
		Statement result = Statement null;

		switch ( parseWord(ci) ) {
			case "DIM": {
				result = parseDIM(ci);
				break;
			}
			case "END": {
				result = parseEND(ci);
				break;
			}
			case "GOTO": {
				result = parseGOTO(ci);
				break;
			}
			case "IF": {
				result = parseIF(ci);
				break;
			}
			case "INPUT": {
				result = parseINPUT(ci);
				break;
			}
			case "LET": {
				result = parseLET(ci);
				break;
			}
			case "PRINT": {
				result = parsePRINT(ci);
				break;
			}
			case "REM": {
				result = parseREM(ci);
				break;
			}
		}

		return result;
	}

	private Statement parseDIM(CharacterIterator ci) throws {
		if ( !ci.hasNext() ) {
			throw new Exception("incomplete DIM!");
		}

		return Statement new DimStatement(parseWord(ci));
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

		return Statement new IfStatement(expression(ci), parseStatement(ci));
	}

	private Statement parseINPUT(CharacterIterator ci) throws {
		if ( !ci.hasNext() ) {
			throw new Exception("incomplete INPUT!");
		}

		return Statement new InputStatement(parseWord(ci));
	}

	private Statement parseLET(CharacterIterator ci) throws {
		if ( !ci.hasNext() ) {
			throw new Exception("incomplete IF!");
		}

		string variable = parseWord(ci);

		skipWhitespaces(ci);

		if ( ci.current() != "=" ) {
			throw "LET: syntax error: missing '='";
		}

		return Statement new LetStatement(variable, expression(ci));
	}

	private Statement parsePRINT(CharacterIterator ci) throws {
		string text = parseWord(ci);

		if ( ci.hasNext() ) {
			throw "cannot handle tokens after print!";
		}

		return Statement new PrintStatement(text);
	}

	private Statement parseREM(CharacterIterator ci) throws {
		// ignore everything on this line
		return Statement new RemStatement(parseLine(ci));
	}


///////////////////////////////////////////////////////////
// Expression parsing

	private Expression expression(CharacterIterator ci) throws {
		//skipWhitespaces(ci);

		var leftExp = expression(parseWord(ci));

		if ( ci.hasNext() ) {
			//skipWhitespaces(ci);

			if ( !ci.hasNext() ) {
				throw "invalid boolean expression!";
			}

			var op = ci.current();

			var rightExp = expression(parseWord(ci));

			var binaryExp = new BinaryExpression(op);
			binaryExp.mLeft = leftExp;		
			binaryExp.mRight = rightExp;	

			return Expression binaryExp;
		}

		return leftExp;
	}

	private Expression expression(string value) const throws {
		if ( isNumber(String(value)) ) {
			return Expression new ConstExpression(int value);
		}
		if ( isVariable(String(value)) ) {
			return Expression new VariableExpression(string value);
		}

		throw "invalid value '" + value + "' provided!";
	}


// Expression parsing
///////////////////////////////////////////////////////////

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

	private void skipWhitespaces(CharacterIterator it) const throws {
		while ( WHITESPACES.Contains(it.current()) ) {
			print("Skipping '" + it.current() + "'");

			it.next();
		}
	}
}

