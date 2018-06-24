#!/usr/local/bin/oscript

import Writer;


public void Main(int argc, string args) {
	assert( TestCase1() );
    assert( TestCase2() );
}

bool TestCase1() {
    print("Test Case 1: JsonWriter");

    var writer = new JsonWriter();

    var value = new JsonValue("value", "value");
    print(writer.toString(value));

    var obj = new JsonObject("object", value);
    print(writer.toString(obj));

    obj.addMember(new JsonObject("sub", new JsonValue("value", "element")));
    print(writer.toString(obj));

    return true;
}

bool TestCase2() {
    print("Test Case 2: JsonStyledWriter");

    var writer = new JsonStyledWriter();
/*
    var value = new JsonValue("value");
    print(writer.toString(value));

    var obj = new JsonObject("key", value);
    print(writer.toString(obj));

    obj.addMember(new JsonObject("sub", new JsonValue("element")));
    print(writer.toString(obj));
*/

	var array = new JsonArray("array");
    print(writer.toString(array));
    print(writer.toString2(JsonValue array));
    print("");

    array.addMember(new JsonValue("key1", "value"));
    array.addMember(new JsonObject("key2", new JsonValue("inner", "value")));

    print(writer.toString(array));
    print(writer.toString2(JsonValue array));

    return true;
}

