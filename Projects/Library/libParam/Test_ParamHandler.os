#!/usr/local/bin/slang

import ParameterHandler;

public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

bool TestCase1() {
	print( "TestCase 1" );

	try {
		int argc = 2;
		string args = "./Test_ParameterHandler.os \"this is a parameter\"";

		var params = new ParameterHandler( argc, args, false );

		{	// debug print
			int count;
			foreach ( Parameter param : params ) {
				print( cast<string>( count++ ) + ": " + param.toString() );
			}
		}
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
		assert( false );
	}

	return true;
}

bool TestCase2() {
	print( "TestCase 2" );

	int argc = 4;
	string args = "--one=true --two --three= four";

	var params = new ParameterHandler( argc, args, false );

	{	// debug print
		int count;
		foreach ( Parameter param : params ) {
			print( cast<string>( count++ ) + ": " + param.toString() );
		}
	}

	assert( params.size() == argc );


	Parameter param;

	{	// --one=true
		param = params[0];
		assert( "true" == string param );

		print( "Key: " + param.Key );
		assert( param.Key == "one" );

		print( "Value: " + param.Value );
		assert( param.Value == "true" );
	}

	{	// --two
		param = params[1];
		assert( param == "two" );

		print( "Key: " + param.Key );
		assert( param.Key == "two" );

		print( "Value: " + param.Value );
		assert( param.Value == "" );
	}

	{	// --three=
		param = params[2];
		assert( param == "three" );

		print( "Key: " + param.Key );
		assert( param.Key == "three" );

		print( "Value: " + param.Value );
		assert( param.Value == "" );
	}

	{	// four
		param = params[3];
		assert( param == "four" );

		print( "Key: " + param.Key );
		assert( param.Key == "four" );

		print( "Value: " + param.Value );
		assert( param.Value == "" );
	}

	{	// remove a parameter
		param = params[2];
		assert( param == "three" );
		assert( params.size() == 4 );

		params.remove( "three" );

		assert( params.size() == 3 );
	}

	return true;
}

private bool TestCase3() {
	print( "TestCase 3: throw exception if key does not exist" );

	int argc = 1;
	string args;

	var params = new ParameterHandler( argc, args, false );

	try {
		print( params[ "key" ] );
	}
	catch ( IException e ) {
		print( "Nice! Exception: " + e.what() + " occurred correctly" );
		return true;
	}

	return false;
}
