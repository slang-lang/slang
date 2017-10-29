#!/usr/local/bin/oscript

private object TestObject {
	public int mValue;

	public void Constructor(int value = 0) {
		mValue = value;
	}

/*
	public bool operator<(TestObject other const) const {
		//print((string mValue) + " < " + (string other.mValue));
		return mValue < other.mValue;
	}
*/
}

public void Main(int argc, string args) {
	print("Comparison");

	TestObject obj1 = new TestObject(1);
	TestObject obj2 = new TestObject(2);

	assert( obj1 != obj2 );
	assert( obj1 < obj2 );
	//assert( obj2 < obj1 );
}

