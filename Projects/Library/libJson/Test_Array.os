#!/usr/local/bin/slang

// Library imports

// Project imports
import Array;
import Object;

public void Main(int argc, string args) {
	assert( TestCase1() );
}

private bool TestCase1() {
	var array = new JsonArray();

	print( array.toString() );

	array.addMember( new JsonValue( 173 ) );
	array.addMember( new JsonValue( "1389" ) );
	array.addMember( new JsonArray() );

	print( array.toString() );

	foreach ( JsonValue value : array ) {
		//print( value.toString() );
	}

	var value const = array[1];
	//print( array[1].asString() );
	assert( value.asString() == "1389" );

	return true;
}

