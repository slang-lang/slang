#!/usr/local/bin/oscript

// library imports
import System.CharacterIterator;
import System.Collections.Map;
import System.IO.File;

// project imports
import Line;
import Scanner;


public object Parser {
	private string COMPARECHARS const = "<>=";
	private string DELIMITERCHARS const;
	private string OPERATORCHARS const = "+-*/";

	public void Constructor() {
		DELIMITERCHARS = COMPARECHARS + OPERATORCHARS;
	}

	public Map<int, Line> parseFile(string filename) modify {
		Scanner scanner = new Scanner(new System.IO.File(filename, "r"), ascii(10));

		print("Parsing file '" + filename + "'...");

		StringIterator it = scanner.getIterator();
		Map<int, Line> lines = new Map<int, Line>();
		Line previousLine;

		while ( it.hasNext() ) {
			if ( it.current() ) {
				print(it.current());

				Line line = parseLine(it.current());

				lines.insert(line.mLineNumber, line);

				if ( previousLine ) {
					previousLine.nextLine(line.mLineNumber);
				}

				previousLine = line;
			}

			it++;
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

		throw "IF-branch not implemented!";
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

		throw "LET-branch not implemented!";
	}

	private Statement parsePRINT(CharacterIterator ci) throws {
		string text;

		while ( ci.hasNext() ) {
			string c = ci.current();
			ci++;

			text += c;
		}

		return Statement new PrintStatement(text);
	}

	private Statement parseREM(CharacterIterator ci) throws {
		// ignore everything on this line
		return Statement new RemStatement(parseLine(ci));
		//return Statement new RemStatement();
	}

	private string parseLine(CharacterIterator ci) throws {
		string line;

		while ( ci.hasNext() ) {
			string c = ci.current();
			ci++;

			line += c;
		}

		return line;
	}

	private string parseWord(CharacterIterator ci) throws {
		string word;

		while ( ci.hasNext() ) {
			string c = ci.current();
			ci++;

			if ( c == " " ) {
				break;
			}

			word += c;
		}

		return word;
	}
}

