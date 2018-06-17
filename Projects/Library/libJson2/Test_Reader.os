#!/usr/local/bin/oscript

import Reader;

public void Main(int argc, string args) {
	assert( TestCase1() );
}

bool TestCase1() {
	var str = "{ \"key\": \"value\" }";

	var reader = new JsonReader();
	var value = reader.process(str);
	assert( value );

	print(value.toString());

	return true;
}

