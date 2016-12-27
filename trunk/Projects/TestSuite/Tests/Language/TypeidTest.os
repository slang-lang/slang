#!/usr/local/bin/oscript

public void Main(int argc = 0, string args = "") {
	int intValue;
	string stringValue;
	Object objectValue;

	print(typeid(intValue));
	assert( typeid(intValue) == "int" );

	print(typeid(stringValue));
	assert( typeid(stringValue) == "string" );

	print(typeid(objectValue));
	assert( typeid(objectValue) == "Object" );
}

