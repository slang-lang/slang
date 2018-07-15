#!/usr/local/bin/oscript

import ParameterHandler;

public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
}

bool TestCase1() {
	print("TestCase 1");

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
		assert( false );
	}

	return true;
}

bool TestCase2() {
	print("TestCase 2");

	int argc = 3;
	string args = "--one=true" + ascii(10) + "--two" + ascii(10) + "--three=";

	var params = new ParameterHandler(argc, args);

	assert( params.size() == argc );


	Parameter param = params.at(0);
	print(string param);

	assert( "--one=true" == string param );

	print("Key: " + param.Key);
	assert( param.Key == "one" );

	print("Value: " + param.Value);
	assert( param.Value == "true" );


	param = params.at(1);
	print("FullValue: " + string param);

	assert( "two" == string param );

	print("Key: " + param.Key);
	assert( param.Key == "two" );

	assert( param.Value == "two" );


	param = params.at(2);
	print(string param);

	assert( "--three=" == string param );

	print("Key: " + param.Key);
	assert( param.Key == "three" );

	print("Value: " + param.Value);
	assert( param.Value == "" );

	return true;
}

