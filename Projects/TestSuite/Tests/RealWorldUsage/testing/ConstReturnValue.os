#!/usr/local/bin/slang

object TestObject {
	public int mValue;
}

public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
}

int const ConstReturnValue() const {
	return 17;
}

TestObject const ReturnConstObject() const {
	return new TestObject();
}

bool TestCase1() {
	print("TestCase 1: Type declaration");

	TestObject obj1 = ReturnConstObject();
	obj1.mValue = 1;

	assert( !"this is wrong!" );

	return false;
}

bool TestCase2() {
	print("TestCase 2: Type inference");

	var obj2 = ReturnConstObject();
	obj2.mValue = 2;

	assert( !"this is wrong!" );

	return false;
}

bool TestCase3() {
	print("TestCase 3: Type declaration");

	int value = ConstReturnValue();
	value = 3;

	assert( "this is correct" );

	return true;
}

bool TestCase4() {
	print("TestCase 4: Type inference");

	var value = ConstReturnValue();
	value = 4;

	assert( "this is correct" );

	return true;
}

