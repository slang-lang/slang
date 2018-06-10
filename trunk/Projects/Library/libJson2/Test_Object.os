#!/usr/local/bin/oscript

import Object;

public void Main(int argc, string args) {
	assert(TestCase1());
}

bool TestCase1() {
	var value = new Json.Object("key", new Json.Value("value"));
	print(value.toString());

	var o1 = new Json.Object("o1", Json.Value new Json.Object("o2", Json.Value new Json.Object("o3", new Json.Value("level 3")) ) );
	print(o1.toString());

	return bool value;
}

