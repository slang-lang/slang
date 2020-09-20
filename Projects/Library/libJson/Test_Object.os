#!/usr/local/bin/slang

// Library imports

// Project imports
import Object;

public void Main(int argc, string args) {
	assert( TestCase1() );
}

private bool TestCase1() {
	try {
		var value = new JsonObject( "key", new JsonValue( "value" ) );
		print( value.toString() );
		value.set( "key", new JsonValue( "bla" ) );
		print( value.toString() );

		var o1 = new JsonObject(
			"o1",
			JsonValue new JsonObject(
				"o2",
				JsonValue new JsonObject(
					"o3",
					new JsonValue("level 3")
				)
			)
		);
		print( o1.toString() );

		o1.addMember( "another", new JsonValue( "object" ) );
		print( o1.toString() );

		assert( o1.isMember( "o1" ) );
		var valo1 const = JsonObject o1[ "o1" ];

		assert( valo1.isMember( "o2" ) );
		var tmpObj = JsonObject valo1[ "o2" ];
		print( tmpObj.toString() );

		assert( tmpObj.isMember( "o3" ) );
		assert( ! tmpObj.isMember( "o4" ) );
		tmpObj = tmpObj[ "o3" ];
		print( tmpObj.toString() );

		return bool value;
	}
	catch ( string e ) {
		print( "Exception: " + e );
	}
	catch ( IException e ) {
		print( "Exception: " + e.what() );
	}

	return false;
}

