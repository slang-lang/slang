#!/usr/local/bin/slang

// Library imports

// Project imports
import Reader;


public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
}

private bool TestCase1() {
    try {
        //var str = "{ \"key1\": \"value\" }";
        //var str = "{ \"key1\": \"value\", \"key2\": \"value\", \"key3\": \"value\" }";
        //var str = "[]";
        //var str = "{ \"key1\": [1, 2] }";
        var str = "{ \"key1\": [ { \"key2\": \"value\" }, 2] }";

        print( str );               // input string

        var reader = new JsonReader();
        var value = reader.parse( str );
        assert( value );

        print( value.toString() );  // output string

        return true;
   }
   catch ( string e ) {
	   print( "Exception: " + e );
   }
   catch ( IException e ) {
	   print( "Exception: " + e.what() );
   }

   return false;
}

private bool TestCase2() {
	print( "Read negative number" );

	try {
		var str = "{ \"key\": -1 }";
		print( str );

		var reader = new JsonReader();
		var value = reader.parse( str );
		assert( value );

		print( value.toString() );

		return true;
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}

	return false;
}

private bool TestCase3() {
	print( "Read exponential number" );

	try {
		var str = "{ \"key\": 7e-5 }";
		print( str );

		var reader = new JsonReader();
		var value = reader.parse( str );
		assert( value );

		print( value.toString() );

		return true;
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}

	return false;
}

private bool TestCase4() {
	print( "TestCase 4: escape sequences" );

	try {
		var str = "{ \"key\": \"string \\\"escape\\\" string\" }";
		print( str );

		var reader = new JsonReader();
		var value = reader.parse( str );
		assert( value );

		print( value.toString() );

		return true;
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}

	return false;
}

private bool TestCase5() {
	print( "TestCase 5: null values" );

	try {
		var str = "{ \"key\": null }";
		print( str );

		var reader = new JsonReader();
		var value = reader.parse( str );
		assert( value );

		print( value.toString() );

		return true;
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}

	return false;
}

