#!/usr/local/bin/slang

// library imports
import libParam;
import System.Collections.List;
import System.IO.File;
import System.String;
import System.StringIterator;

// project imports
import Consts;
import Debugger;


// public variables
string filename;


public int Main(int argc, string args) modify {
	var debug = false;
	var params = new ParameterHandler(argc, args);

	// Handle parameters
	// {
	if ( params.contains("debug") ) {
		debug = true;
		params.remove("debug");
	}

	if ( params.contains("version") ) {
		print(APPNAME + " " + VERSION);
		return 0;
	}
	// }

	if ( !params.empty() ) {
		// set filename if any params are set
		filename = cast<string>( params[ 0 ].Key );
	}

	try {
		while ( true ) {
			write("DBasic> ");

			var commandIt = new StringIterator(cin());
			if ( !commandIt.hasNext() ) {
				continue;
			}

			switch ( commandIt.next() ) {
				case "help": { printHelp(); break; }
				case "load": { loadFile(commandIt); break; }
				case "run": { run(commandIt); break; }
				case "quit": { print("Quitting..."); return 0; }
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

	return 0;
}

void loadFile(StringIterator it) modify {
	if ( !it.hasNext() ) {
		print("filename expected!");
		return;
	}

	filename = it.next();
}

void printHelp() {
	print("");
	print("Available commands:");
	print("help    This screen");
	print("load    Loads a file for execution");
	print("run     Starts a debugging session for the loaded file");
	print("quit    Quits the debugger");
	print("");
}

void run(StringIterator it) modify {
	if ( it.hasNext() ) {
		loadFile(it);
	}

	if ( !filename ) {
		print("no file selected for debugging");
		return;
	}

	try {
		Debugger debugger = new Debugger(filename);

		print("Started debug session...");
		print("");

		debugger.run();

		print("");
		print("Debug session exited.");
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch {
		print("Exception: caught unknown exception!");
	}
}

