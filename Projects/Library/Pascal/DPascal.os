#!/usr/local/bin/slang

// library imports
import libParam.ParameterHandler;
import System.String;
import System.StringIterator;

// project imports
import Consts;
import Debugger;
import Parser;


public object PascalDebugger {
	public void Constructor(int argc, string args) {
		var params = new ParameterHandler(argc, args);

		if ( params.contains("debug") ) {
			mDebugMode = true;
			params.remove("debug");
		}

		if ( params.contains("version") ) {
			print(APPNAME + " " + VERSION);
			return;
		}

		if ( !params.empty() ) {
			// load file if any params are set
			loadFile(params.at(0).Key);
		}
	}

	public void run() modify {
		try {
			while ( true ) {
				write("DPascal> ");

				var commandIt = new StringIterator(cin());
				if ( !commandIt.hasNext() ) {
					continue;
				}

				switch ( commandIt.next() ) {
					case "help": { printHelp(); break; }
					case "load": { loadFile(commandIt.next()); break; }
					case "run": { run(commandIt); break; }
					case "quit": { print("Quitting..."); return; }
					default: { print("Invalid command"); break; }
				}
			}
		}
		catch ( string e ) {
			print("Exception: " + e);
		}
		catch ( IException e ) {
			print("Exception: " + e.what());
		}
		catch {
			print("Exception: uncaught exception!");
		}
	}

	private void loadFile(string filename) modify {
		if ( !filename ) {
			print("filename expected!");
			return;
		}

		var parser = new Parser();
		mProgram = parser.parseFile(filename, mDebugMode);

		if ( mDebugMode ) {
			print("");
			print(mProgram.toString());
			print("");
		}
	}

	private void printHelp() {
		print("");
		print("Available commands:");
		print("help    This screen");
		print("load    Loads a file for execution");
		print("run     Starts a debugging session for the loaded file");
		print("quit    Quits the debugger");
		print("");
	}

	private void run(StringIterator it) modify {
		if ( it.hasNext() ) {
			loadFile(it.next());
		}

		if ( !mProgram ) {
			print("no file selected for debugging");
			return;
		}

		try {
			var debugger = new Debugger(mProgram);

			print("Started debug session...");
			print("");

			debugger.run();

			print("");
			print("Debug session exited.");
		}
		catch ( string e ) {
			print("Error: " + e);
		}
		catch ( IException e ) {
			print("Error: " + e.what());
		}
		catch {
			print("Error: caught unknown exception!");
		}
	}

	private bool mDebugMode;
	private string mFilename;
	private Statement mProgram;
} 


public void Main(int argc, string args) modify {
	var debugger = new PascalDebugger(argc, args);
	debugger.run();
}

