#!/usr/local/bin/oscript

// Library imports
import libParam.ParameterHandler;
import System.IO.File;

// Project imports
import Scanner;


public void Main(int argc, string args) {
	if ( argc < 2 ) {
		print("usage: program [arg1 [arg2 [...] ] ]");
		return;
	}

	try {
		var params = new ParameterHandler(argc, args, true);

		foreach ( Parameter filename : params ) {
			if ( params.size() > 2 ) {
				print(filename.Value + ":");
			}

			foreach ( string line : new Scanner(new System.IO.File(filename.Value, System.IO.FileAccessMode.ReadOnly), LINEBREAK) ) {
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

