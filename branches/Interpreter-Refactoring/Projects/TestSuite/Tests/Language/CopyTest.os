#!/usr/local/bin/oscript

public object TestObject {
	private int mValue;

	public void TestObject(int value) {
		mValue = value;
	}
}

public void Main(int argc, string args) modify {
	assert( TestCase1() );
}

private bool TestCase1() modify {
	TestObject obj1 = new TestObject(173);
	TestObject obj2;

	obj2 = copy obj1;

	assert(obj2);

	print("obj1.mValue = " + obj1.mValue + " vs obj2.mValue = " + obj2.mValue);

	obj2.mValue = 1389;

	print("obj1.mValue = " + obj1.mValue + " vs obj2.mValue = " + obj2.mValue);

	return obj1.mValue != obj2.mValue;
}

