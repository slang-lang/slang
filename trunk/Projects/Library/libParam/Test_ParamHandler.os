#!/usr/local/bin/oscript

import ParameterHandler;

public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
}

bool TestCase1() {
	try {
		int argc = 2;
		string args = "./Test_ParameterHandler.os" + ascii(10) + "this is a parameter\"";

		var params = new ParameterHandler(argc, args);

		int count;
		foreach ( Parameter param : params ) {
			print((string count++) + ": " + param.FullValue);
		}
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}

	return true;
}

bool TestCase2() {
	int argc = 2;
	string args = "--useParam=true" + ascii(10) + "--one";

	var params = new ParameterHandler(argc, args);

	assert( params.size() == 2 );

	foreach ( Parameter param : params ) {
		print(string param);
		assert( "--useParam=true" == string param );

		print("Key: " + param.Key);
		assert( param.Key == "useParam" );

		print("Value: " + param.Value);
		assert( param.Value == "true" );

		break;
	}

	return true;
}

