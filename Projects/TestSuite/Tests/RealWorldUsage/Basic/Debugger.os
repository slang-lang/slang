
// library imports
import System.Collections.Set;

// project imports
import Breakpoint;
import Interpreter;


public object Debugger extends Interpreter {
	private Set<Breakpoint> mBreakpoints;

	public void Constructor(Object lines) {
		base.Constructor(lines);

		mBreakpoints = new Set<Breakpoint>();
	}

	private void addBreakpoint(int line) modify {
		print("Adding breakpoint at line " + line);

		mBreakpoints.insert(new Breakpoint(line));
	}

	private void addBreakpoint(StringIterator it) modify {
		if ( !it.hasNext() ) {
			print("invalid breakpoint!");
			return;
		}

		addBreakpoint(int it.next());
	}

	private void printBreakpoints() const {
		foreach ( Breakpoint line : mBreakpoints ) {
			print("Line " + string line);
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
		foreach ( string variable : mVariables ) {
			printVariable(variable);
		}
	}

	private int processBreakpoint(Line line) modify throws {
		print("> " + line.toPrettyString());

		while ( true ) {
			write("debug> ");

			var cmdIt = new StringIterator(cin());
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
				case "m": { write("Enter variable: "); setVariable(cin()); break; }
				case "n": { return -1; }
				case "p": { printVariable(cmdIt); break; }
				case "quit": { print("Aborting debug session..."); throw ControlFlow.Exit; }
			}
		}

		return 0;
	}

	private void removeBreakpoint(int line) modify {
		int index = mBreakpoints.indexOf(new Breakpoint(line));
		if ( index != -1 ) {
			mBreakpoints.erase(index);
		}
	}

	public int run(bool breakOnFirstLine = true) modify throws {
		if ( !mLines || mLines.empty() ) {
			throw new Exception("no valid lines to interpret!");
		}

		bool breakOnNextLine = breakOnFirstLine;
		int lineNumber = 10;
		Line line;

		try {
			while ( lineNumber > 0 ) {
				line = mLines.get(lineNumber);

				if ( breakOnNextLine || mBreakpoints.contains(new Breakpoint(lineNumber)) ) {
					breakOnNextLine = false;

					lineNumber = processBreakpoint(line);

					if ( lineNumber > 0 ) {
						// jump to given line
						continue;
					}
					else if ( lineNumber == -1 ) {
						breakOnNextLine = true;
					}
				}

				lineNumber = process(line.mStatement) ?: line.nextLine();
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

	private void setVariable(string variable) modify {
		try {
			var obj = mVariables.get(variable);

			write("Enter value: ");
			obj = cin();
		}
		catch {
			print("Unknown variable '" + variable + "'!");
		}
	}
}
