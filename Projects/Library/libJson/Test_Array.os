#!/usr/local/bin/oscript

// Library imports

// Project imports
import Array;
import Object;

public void Main(int argc, string args) {
	assert(TestCase1());
}

bool TestCase1() {
	var array = new JsonArray("array");
	print(array.toString());

	array.addMember(new JsonValue(173));
	array.addMember(new JsonValue("1389"));
	print(array.toString());

	//JsonValue tmpObj = array[1];
	//assert( tmpObj.asString() == "1389" );

	return bool array;
}

