#!/usr/local/bin/oscript

import Array;
import Object;

public void Main(int argc, string args) {
	assert(TestCase1());
}

bool TestCase1() {
	var array = new JsonArray("array");
	print(array.toString());

    array.addMember(new JsonObject("1", new JsonValue("value")));
    array.addMember(new JsonObject("2", new JsonValue("value")));
	print(array.toString());

	return bool array;
}

