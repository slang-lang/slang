#!/usr/local/bin/slang

// Library imports

// Project imports
import Writer;


public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
	assert( TestCase6() );
	assert( TestCase7() );
}

private bool TestCase1() {
	print("Test Case 1: JsonWriter - empty values");

	try {
		var writer = new JsonWriter();

		print( "Empty JsonArray:" );
		print( writer.toString( new JsonArray() ) );

		print( "Empty JsonObject:" );
		print( writer.toString( new JsonObject() ) );

		print( "Empty JsonValue:" );
		print( writer.toString( new JsonValue() ) );

		return true;
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}

	return false;
}

private bool TestCase2() {
	print("Test Case 2: JsonStyledWriter - empty values");

	try {
		var writer = new JsonStyledWriter();

		print( "Empty JsonArray:" );
		print( writer.toString( new JsonArray() ) );

		print( "Empty JsonObject:" );
		print( writer.toString( new JsonObject() ) );

		print( "Empty JsonValue:" );
		print( writer.toString( new JsonValue() ) );

		return true;
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}

	return false;
}

private bool TestCase3() {
	print("Test Case 3: JsonWriter - JsonArray");

	try {
		var writer = new JsonWriter();

		var array = new JsonArray();

		print( writer.toString( array ) );

		array.addMember( new JsonValue( 1 ) );
		array.addMember( new JsonValue( 2 ) );
		array.addMember( new JsonValue( 3 ) );

		print( writer.toString( array ) );

		return true;
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}

	return false;
}

private bool TestCase4() {
	print("Test Case 4: JsonWriter - JsonObject");

	try {
		var writer = new JsonWriter();

		var obj = new JsonObject();
		obj.addMember( "key", new JsonValue( "value" ) );
		//obj.addMember( "key", new JsonValue( "value2" ) );

		print( writer.toString( obj ) );

		return true;
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}

	return false;
}

private bool TestCase5() {
	print("Test Case 5: JsonWriter - JsonValue");

	try {
		var writer = new JsonWriter();

		var value = new JsonValue( "value" );
		print( writer.toString( value ) );

		return true;
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}

	return false;
}

private bool TestCase6() {
	print("Test Case 6: JsonWriter - complex");

	try {
		var writer = new JsonWriter();

		var value = new JsonValue( "value" );
		print( writer.toString( value ) );

		var obj = new JsonObject( "object", value );
		print( writer.toString( obj ) );

		obj.addMember( "sub", new JsonValue( "element" ) );
		print( writer.toString( obj ) );

		return true;
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}

	return false;
}

private bool TestCase7() {
	print("Test Case 7: JsonStyledWriter - complex");

	try {
		var writer = new JsonStyledWriter();

		var value = new JsonValue( "value" );
		print( writer.toString( value ) );

		var obj = new JsonObject( "object", value );
		print( writer.toString( obj ) );

		obj.addMember( "sub", new JsonValue( "element" ) );
		print( writer.toString( obj ) );

		return true;
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}

	return false;
}

