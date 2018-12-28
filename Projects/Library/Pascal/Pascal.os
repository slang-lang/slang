#!/usr/local/bin/oscript

// library imports
import libParam.ParameterHandler;
import System.Collections.List;
import System.IO.File;
import System.String;
import System.StringIterator;

// project imports
import Consts;
import Interpreter;
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
		var parser = new Parser();
		var program = parser.parseFile(string params.at(1).Key)

		print("");
		print(program.toString());
		print("");

		var interpreter = new Interpreter(program);
		return interpreter.run();
	}
	catch ( IException e ) {
		print(typeid(e) + ": " + e.what());
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch {
		print("Exception: caught unknown exception!");
	}

	return -1;
}

