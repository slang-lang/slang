#!/usr/local/bin/slang

// Library imports

// Project imports
import Writer;


public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() {
	print("Test Case 1: JsonWriter");

	try {
		var writer = new JsonWriter();

		var value = new JsonValue("value");
		print(writer.toString(value));

		var obj = new JsonObject("object", value);
		print(writer.toString(obj));

		obj.addMember(new JsonObject("sub", new JsonValue("element")));
		print(writer.toString(obj));

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
	print("Test Case 2: JsonStyledWriter");

	try {
		var writer = new JsonStyledWriter();

		var array = new JsonArray("array");
		print(writer.toString(array));
		print(writer.toString2(JsonValue array));

		array.addMember(new JsonValue("value"));
		array.addMember(new JsonObject("key2", new JsonValue("value")));

		print(writer.toString(array));
		print(writer.toString2(JsonValue array));

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

