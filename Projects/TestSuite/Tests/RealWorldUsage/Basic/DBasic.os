#!/usr/local/bin/oscript

// library imports
import System.Collections.List;
import System.IO.File;
import System.String;
import System.StringIterator;

// project imports
import Debugger;
import Interpreter;
import Line;
import Parser;


// public variable
string filename;


public int Main(int argc, string args) modify {
	parseParameters(argc, args);

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
			}
		}
	}
	catch ( IException e ) {
		print(e.what());
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

void parseParameters(int argc, string args) modify {
	if ( argc < 2 ) {
		// not enough params set
		return;
	}

	var params = new List<String>();

	foreach ( string p : new String(args) ) {
		params.push_back(new String(p));
	}

	// set filename if any params are set
	filename = string params.at(1);
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
		Parser parser = new Parser();
		Debugger debugger = new Debugger(Object parser.parseFile(filename));

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

