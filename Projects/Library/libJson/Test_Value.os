#!/usr/local/bin/slang

// Library imports

// Project imports
import Value;


public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

private bool TestCase1() {
	print( "Test Case 1: basic JsonValue" );

	var value = new JsonValue( "string_value" );
	print( value.toString() );

	return bool value;
}

private bool TestCase2() {
	print( "Test Case 2: JsonValue with JsonObject" );

	var value = new JsonValue( new JsonObject( "key", new JsonValue( "value" ) ) );
	print( value.toString() );

	return bool value;
}

private bool TestCase3() {
	print( "Test Case 3: JsonValue is null" );

	var value = new JsonValue();
	print( value.toString() );

	return bool value.isNull();
}

