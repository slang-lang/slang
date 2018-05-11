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


public int Main(int argc, string args) modify {
	if ( argc < 2 ) {
		print("not enought parameters provided!");
		return -1;
	}


	List<String> params = new List<String>();

	foreach ( string p : new String(args) ) {
		params.push_back(new String(p));
	}

	try {
		Parser parser = new Parser();

		Interpreter interpreter = new Interpreter(Object parser.parseFile(string params.at(1)));
		return interpreter.run();
	}
	catch ( IException e ) {
		print(e.what());
	}
	catch ( string e ) {
		print(e);
	}
	catch {
		print("caught unknown exception!");
	}

	return -1;
}

