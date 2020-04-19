#!/usr/local/bin/slang

// library imports
import libParam.ParameterHandler;

// project imports
import Consts;
import Interpreter;
import Parser;


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

	if ( params.empty() ) {
		print("not enought parameters provided!");
		return -1;
	}
	// }

	try {
		var parser = new Parser();
		var program = parser.parseFile(params.at(0).Key, debug);

		if ( debug ) {
			print("");
			print(program.toString());
			print("");
		}

		var interpreter = new Interpreter(program);
		return interpreter.run(debug);
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

	return -1;
}

