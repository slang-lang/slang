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
		string args = "./Test_ParameterHandler.os \"this is a parameter\"";

		var params = new ParameterHandler(argc, args);

		{	// debug print
			int count;
			foreach ( Parameter param : params ) {
				print((string count++) + ": " + param.debug());
			}
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

	int argc = 4;
	string args = "--one=true --two --three= four";

	var params = new ParameterHandler(argc, args);

	{	// debug print
		int count;
		foreach ( Parameter param : params ) {
			print((string count++) + ": " + param.debug());
		}
	}

	assert( params.size() == argc );


	Parameter param;

	{	// --one=true
		param = params.at(0);
		assert( "true" == string param );

		print("Key: " + param.Key);
		assert( param.Key == "one" );

		print("Value: " + param.Value);
		assert( param.Value == "true" );
	}

	{	// --two
		param = params.at(1);
		assert( param == "two" );

		print("Key: " + param.Key);
		assert( param.Key == "two" );

		print("Value: " + param.Value);
		assert( param.Value == "" );
	}

	{	// --three=
		param = params.at(2);
		assert( param == "three" );

		print("Key: " + param.Key);
		assert( param.Key == "three" );

		print("Value: " + param.Value);
		assert( param.Value == "" );
	}

	{	// four
		param = params.at(3);
		assert( param == "four" );

		print("Key: " + param.Key);
		assert( param.Key == "four" );

		print("Value: " + param.Value);
		assert( param.Value == "" );
	}

	return true;
}

