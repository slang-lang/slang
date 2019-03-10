#!/usr/local/bin/oscript

// library imports
import libParam.ParameterHandler;
import System.Collections.List;
import System.IO.File;
import System.String;
import System.StringIterator;

// project imports
import Consts;
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
	if ( params.contains("version") ) {
		print(APPNAME + " " + VERSION);
		return 0;
	}

	try {
		Parser parser = new Parser();

		Interpreter interpreter = new Interpreter(Object parser.parseFile(params.at(0).Key));
		return interpreter.run();
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch ( IException e ) {
		print(typeid(e) + ": " + e.what());
	}
	catch {
		print("Exception: caught unknown exception!");
	}

	return -1;
}

