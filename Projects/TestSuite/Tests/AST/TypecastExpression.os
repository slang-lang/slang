#!/usr/local/bin/slang

import System.String;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	//assert( TestCase5() );
}

private bool TestCase1() {
	print("TestCase 1: atomic types");

	int value = 173;

	print( "\"173\" == cast<string>( value ) = " + ("173" == cast<string>( value )) );

	return "173" == cast<string>( value );
}

private bool TestCase2() {
	print("TestCase 2: cast String to string");

	print( "\"173\" == cast<string>( new String( 173 ) ) = " + ("173" == cast<string>( new String( 173 ) )) );

	return "173" == cast<string>( new String( 173 ) );
}

private bool TestCase3() {
	print("TestCase 3: downcast String to Object");

	assert( cast<Object>( new String( 173 ) ) );

	return cast<Object>( new String( 173 ) ) != null;
}

private bool TestCase4() {
	print("TestCase 4: upcast Object to String");

	var obj = new String( 173 );

	assert( cast<String>( obj ) );

	return cast<String>( obj ) != null;
}

/*
private bool TestCase5() {
	print("TestCase 5: failing cast");

	var obj = cast<Object>(new String( 173 ));

	assert( cast<string>( obj ) );

	return false;
}
*/

