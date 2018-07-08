#!/usr/local/bin/oscript

import ParameterHandler;

public void Main(int argc, string args) {
	try {
		var params = new ParameterHandler(argc, args);

		int count;
		foreach ( Parameter param : params ) {
			print((string count++) + ": " + param.FullValue);
		}
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}
}

