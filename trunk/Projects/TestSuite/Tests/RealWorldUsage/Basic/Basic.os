#!/usr/local/bin/oscript

// library imports
import System.Collections.List;
import System.IO.File;
import System.String;
import System.StringIterator;

// project imports
import Interpreter;
import Line;
import Parser;


public int Main(int argc, string args) modify {
	List<String> params = new List<String>();

	//int count;
	foreach ( string p : new String(args) ) {
		//print("argv[" + count + "] = " + p);

		params.push_back(new String(p));

		//count++;
	}

	if ( params.size() < 1 ) {
		print("not enought parameters provided!");
		return -1;
	}

	try {
		Parser parser = new Parser();

		Interpreter interpreter = new Interpreter(Object parser.parseFile(string params.at(1)));
		return interpreter.run();
	}
	catch ( ControlFlow e ) {
		switch ( e ) {
			case ControlFlow.Exit: {
				print("ControlFlow: Exit");
				break;
			}
			case ControlFlow.Normal: {
				print("ControlFlow: Normal");
				break;
			}
			default: {
				print("ControlFlow: Unknown!");
				break;
			}
		}
	}
	catch ( Exception e ) {
		print(e.what());
	}
	catch {
		print("caught unknown exception!");
	}

	return -1;
}

