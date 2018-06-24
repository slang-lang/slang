#!/usr/local/bin/oscript

import Object;

public void Main(int argc, string args) {
	assert(TestCase1());
}

bool TestCase1() {
	var value = new JsonObject("key", new JsonValue("key", "value"));
	print(value.toString());

	var o1 = new JsonObject(
		"o1",
		JsonValue new JsonObject(
			"o2",
			JsonValue new JsonObject(
				"o3",
				new JsonValue("key", "level 3")
			)
		)
	);
	print(o1.toString());

	o1.addMember(new JsonObject("another", new JsonValue("key", "object")));
	print(o1.toString());

	return bool value;
}

