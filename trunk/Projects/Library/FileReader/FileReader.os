#!/usr/local/bin/oscript

// Library imports
import libParam.ParameterHandler;

// Project imports
import Scanner;


public void Main(int argc, string args) {
	if ( argc < 2 ) {
		print("usage: program [arg1 [arg2 [...] ] ]");
		print("");
		return;
	}

	try {
		var params = new ParameterHandler(argc, args, true);

		foreach ( Parameter filename : params ) {
			if ( params.size() > 2 ) {
				print(filename.Key + ":");
			}

			foreach ( string line : new Scanner(filename.Key) ) {
				print(line);
			}
		}
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}
}

