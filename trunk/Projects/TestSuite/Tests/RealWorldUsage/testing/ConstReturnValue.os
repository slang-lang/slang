#!/usr/local/bin/oscript

object TestObject {
	public int mValue;
}

public int Main(int argc, string args) {
/*
	var obj1 = ReturnConstObject();
	obj1.mValue = 1;

	assert( !"this is wrong!" );
*/

	TestObject obj2 = ReturnConstObject();
	obj2.mValue = 2;

	assert( !"this is wrong!" );

/*
	int value = ConstReturnValue();
	value = 3;

	assert( "this is correct" );
*/

/*
	var value = ConstReturnValue();
	value = 4;

	assert( "this is correct" );
*/

	return ConstReturnValue();
}

int const ConstReturnValue() const {
	return 17;
}

TestObject const ReturnConstObject() const {
	return new TestObject();
}

