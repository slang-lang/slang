#!/usr/local/bin/oscript

// Library imports

// Project imports
import Object;

public void Main(int argc, string args) {
	assert(TestCase1());
}

bool TestCase1() {
	var value = new JsonObject("key", new JsonValue("value"));
	print(value.toString());

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
	print(o1.toString());

	assert( o1.isMember( "o2" ) );

	o1.addMember(new JsonObject("another", new JsonValue("object")));
	print(o1.toString());

	return bool value;
}

