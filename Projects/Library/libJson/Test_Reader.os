#!/usr/local/bin/slang

// Library imports

// Project imports
import Reader;

public void Main(int argc, string args) {
	assert( TestCase1() );
}

bool TestCase1() {
    try {
        //var str = "{ \"key1\": \"value\" }";
        //var str = "{ \"key1\": \"value\", \"key2\": \"value\", \"key3\": \"value\" }";
        //var str = "[]";
        //var str = "{ \"key1\": [1, 2] }";
        var str = "{ \"key1\": [ { \"key2\": \"value\" }, 2] }";

        print( str );               // input string

        var reader = new JsonReader();
        var value = reader.parse(str);
        assert( value );

        print( value.toString() );  // output string

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

