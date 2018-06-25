#!/usr/local/bin/oscript

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

	return bool array;
}

