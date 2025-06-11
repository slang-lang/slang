#!/usr/bin/env slang

private object TestObject {
	public int mValue;

	public void Constructor(int value) {
		mValue = value;

		print("mValue = " + mValue);
	}

	public TestObject operator=(int value) modify {
		print("operator=(int)");
		mValue = value;

		return this;
	}

	public int =operator(int none) const {
		return mValue;
	}
	public string =operator(string none) const {
		return string mValue;
	}
}

private object AnotherObject {
}

public void Main(int argc, string args) {
	assert( TestCase1() );
	//assert( TestCase2() );
}

private bool TestCase1() {
	print("TestCase 21: TestObject.operator=");

	TestObject obj1 = new TestObject(173);
	print("obj1 = " + string obj1);
	print("obj1.mValue = " + obj1.mValue);

	TestObject obj2 = new TestObject(1389);
	print("obj2 = " + string obj2);
	print("obj2.mValue = " + obj2.mValue);

	obj1 = 664;
	print("obj1.mValue = " + obj1.mValue);

	int value = obj1;
	print("value = " + value);
	value = obj2;
	print("value = " + value);

	return true;
}

private bool TestCase2() {
	print("TestCase 2: AnotherObject = <TestObject>");

	TestObject obj;
	AnotherObject another;

	another = obj;

	return false;
}

