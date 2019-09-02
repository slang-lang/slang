#!/usr/local/bin/oscript

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

        var reader = new JsonReader();
        var value = reader.process(str);
        assert( value );

        print(value.toString());

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

