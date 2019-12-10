
// library imports
import System.Collections.Set;

// project imports
import Parser;
import Interpreter;


public object Debugger extends Interpreter {
	private Set<int> mBreakpoints;
	private Parser mParser;

	public void Constructor(string filename) {
		mBreakpoints = new Set<int>();
		mParser = new Parser();

		base.Constructor(mParser.parseFile(filename));
	}

	private void addBreakpoint(int line) modify {
		print("Adding breakpoint at line " + line);

		mBreakpoints.insert(line);
	}

	private void addBreakpoint(StringIterator it) modify {
		if ( !it.hasNext() ) {
			print("invalid breakpoint!");
			return;
		}

		addBreakpoint(int it.next());
	}

	private void executeCommand(string command) modify {
		var ci = new CharacterIterator(command);

		try {
			var stmt = mParser.parseStatement(ci);
			if ( stmt ) {
				int newLine = process(stmt);

				if ( newLine ) {
					mCurrentLine = newLine;
				}
			}
		}
		catch ( IException e ) {
			print(typeid(e) + ": " + e.what());
		}
	}

	private void modifyVariable(StringIterator si) modify {
		if ( !si.hasNext() ) {
			print("invalid variable name provided!");
		}

		try {
			var obj = mVariables.get(si.next());

			write("Enter value: ");
			obj = cin();
		}
		catch {
			print("Unknown variable '" + si.current() + "'!");
		}
	}

	private void printBreakpoints() const {
		foreach ( int line : mBreakpoints ) {
			print("Line " + line);
		}
	}

	private void printHelp() const {
		print("Available commands:");
		print("b:  Add breakpoint");
		print("breakpoints:  Print all breakpoints");
		print("c:  Continue execution");
		print("d:  Delete breakpoint");
		print("g:  Go to line");
		print("help:  Print help (= this screen)");
		print("l:  List program");
		print("ll: Print current line");
		print("m:  Modify variable");
		print("n:  Execute next line and break on execution");
		print("p:  Print variable(s)");
		print("q:  Quit debugger");
	}

	private void printProgram() const {
		foreach ( Pair<int,Line> line : mLines ) {
			print(line.second.toPrettyString());
		}
	}

	private void printVariable(string variable) const {
		try {
			print(variable + " = " + string mVariables.get(variable));
		}
		catch {
			print("Unknown variable '" + variable + "'!");
		}
	}

	private void printVariable(StringIterator it) const {
		if ( !it.hasNext() ) {
			return printVariables();
		}

		return printVariable(it.next());
	}

	private void printVariables() const {
		foreach ( Pair<string, String> p : mVariables ) {
			printVariable(p.first);
		}
	}

	private int processBreakpoint(Line line) modify throws {
		print("> " + line.toPrettyString());

		while ( true ) {
			write("debug> ");

			string command = cin();

			var cmdIt = new StringIterator(command);
			if ( !cmdIt.hasNext() ) {
				continue;
			}

			switch ( cmdIt.next() ) {
				case "b": { addBreakpoint(cmdIt); break; }
				case "breakpoints": { printBreakpoints(); break; }
				case "c": { return 0; }
				case "d": { write("Delete breakpoint: "); removeBreakpoint(int cin()); break; }
				case "g": { write("Go to line: "); return int cin(); }
				case "h": { printHelp(); break; }
				case "help": { printHelp(); break; }
				case "l": { printProgram(); break; }
				case "ll": { print("> " + line.toString()); break; }
				case "m": { modifyVariable(cmdIt); break; }
				case "n": { return -1; }
				case "p": { printVariable(cmdIt); break; }
				case "quit": { print("Aborting debug session..."); throw ControlFlow.Exit; }
				default: { executeCommand(command); break; }
			}
		}

		return 0;
	}

	private void removeBreakpoint(int line) modify {
		int index = mBreakpoints.indexOf(line);
		if ( index != -1 ) {
			mBreakpoints.erase(index);
		}
	}

	public int run(bool breakOnFirstLine = true) modify throws {
		if ( !mLines || mLines.empty() ) {
			throw new Exception("no valid lines to interpret!");
		}

		mForStack.clear();
		mVariables.clear();

		try {
			bool breakOnNextLine = breakOnFirstLine;
			Line line;

			while ( mCurrentLine > 0 ) {
				line = mLines.get(mCurrentLine);

				if ( breakOnNextLine || mBreakpoints.contains(mCurrentLine) ) {
					breakOnNextLine = false;

					mCurrentLine = processBreakpoint(line);

					if ( mCurrentLine > 0 ) {
						// jump to given line
						continue;
					}
					else if ( mCurrentLine == -1 ) {
						breakOnNextLine = true;
					}
				}

				mCurrentLine = process(line.mStatement) ?: line.nextLine();
			}
		}
		catch ( ControlFlow e ) {
			switch ( e ) {
				case ControlFlow.Exit: {
					//print("ControlFlow: Exit");
					break;
				}
				case ControlFlow.Normal: {
					//print("ControlFlow: Normal");
					break;
				}
				default: {
					print("ControlFlow: Unknown!");
					break;
				}
			}
		}

		return 0;
	}
}

