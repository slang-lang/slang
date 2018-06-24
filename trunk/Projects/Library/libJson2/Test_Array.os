#!/usr/local/bin/oscript

import Array;
import Object;

public void Main(int argc, string args) {
	assert(TestCase1());
}

bool TestCase1() {
	var array = new JsonArray("array");
	print(array.toString());

    array.addMember(new JsonValue("key1", "value"));
    array.addMember(new JsonValue("key2", "value"));
	print(array.toString());

	return bool array;
}

