#!/usr/local/bin/oscript

import Writer;


public void Main(int argc, string args) {
	assert(TestCase1());
}

bool TestCase1() {
    var value = new JsonValue("value");

    var writer = new JsonWriter();
    print(writer.toString(value));

    var obj = new JsonObject("key", value);
    print(writer.toString(obj));

    obj.addMember(new JsonObject("sub", new JsonValue("element")));
    print(writer.toString(obj));

    return true;
}

