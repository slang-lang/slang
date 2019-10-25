#!/usr/local/bin/oscript

public object TestObject {
	public int mValue;

	public void Constructor(int value) {
		print("TestObject.Constructor(" + value + ")");
		mValue = value;
	}

	public TestObject Copy() {
		print("TestObject.Copy()");
		return new TestObject(mValue);
	}
}

public void Main(int argc = 0, string args = "") modify {
	assert( TestCase1() );
}

private bool TestCase1() modify {
	TestObject obj1 = new TestObject(173);
	assert(obj1);

	TestObject obj2 = copy obj1;
	assert(obj2);

	assert( obj1 != obj2 );

	print("obj1.mValue = " + obj1.mValue + " vs obj2.mValue = " + obj2.mValue);
	assert( obj1.mValue == obj2.mValue );

	obj2.mValue = 1389;

	print("obj1.mValue = " + obj1.mValue + " vs obj2.mValue = " + obj2.mValue);
	assert( obj1.mValue != obj2.mValue );

	return obj1.mValue != obj2.mValue;
}

