#!/usr/local/bin/oscript

// library imports
import libParam.ParameterHandler;
import System.Collections.List;
import System.IO.File;
import System.String;
import System.StringIterator;

// project imports
import Debugger;
import Interpreter;
import Line;
import Parser;


public int Main(int argc, string args) modify {
	if ( argc < 2 ) {
		print("not enought parameters provided!");
		return -1;
	}

	var params = new ParameterHandler(argc, args);

	try {
		Parser parser = new Parser();

		Interpreter interpreter = new Interpreter(Object parser.parseFile(string params.at(1)));
		return interpreter.run();
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

	return -1;
}
