#!/usr/bin/env slang

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

	print( typeid( 17 ) );
	assert( typeid( 17 ) == "int" );

	print( typeid( 2147483647 ) );
	assert( typeid( 2147483647 ) == "int" );

	print( typeid( 2147483650 ) );
	assert( typeid( 2147483650 ) == "int64" );
}

