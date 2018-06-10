#!/usr/local/bin/oscript

import Value;


public void Main(int argc, string args) {
	assert(TestCase1());
}

private bool TestCase1() {
	var value = new Json.Value("value");
	print(value.toString());

	return bool value;
}

