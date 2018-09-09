#!/usr/local/bin/oscript

object TestObject {
	public int mValue;
}

public int Main(int argc, string args) {
	var obj = ReturnConstObject();
	obj.mValue = 5;
	assert( !"obj should be const!" );

	return ConstReturnValue();
}

int const ConstReturnValue() {
	return 17;
}

TestObject const ReturnConstObject() {
	var obj = new TestObject();

	return obj;
}

