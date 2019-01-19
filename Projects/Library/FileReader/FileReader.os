#!/usr/local/bin/oscript

// Library imports
import libParam.ParameterHandler;
import System.IO.File;

// Project imports

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

			readFile(filename.Key);
		}
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}
}

private void readFile(string filename) const {
	var file = new System.IO.File(filename, System.IO.FileAccessMode.ReadOnly);
	string text;

	while ( !file.isEOF() ) {
		text += file.readChar();
	}

	print(text);
}

