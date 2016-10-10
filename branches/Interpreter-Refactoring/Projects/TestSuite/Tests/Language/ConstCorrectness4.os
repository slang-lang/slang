#!/usr/local/bin/oscript

private object TestObject {
	private int mValue;

	public int getValue() const {
		return mValue;
	}

	public void setValue(int value) modify {
		mValue = value;
	}

	public int =operator(int other) const {
		print("=operator(int)");
		return mValue;
	}
	public string =operator(string other) const {
		print("=operator(string)");
		return "{ mValue: " +  mValue + " }";
	}

	public void operator=(int other) modify {
		print("operator=(int)");
		mValue = other;
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

private bool TestCase1() const {
	print("TestCase 1");

	TestObject obj = new TestObject();

	print("obj = " + obj);

	obj = 1;

	print("obj = " + obj);

	return true;
}

private bool TestCase2() const {
	print("TestCase 2");

	TestObject obj = new TestObject();

	print("obj = " + obj);
	{
		obj.setValue(6);
	}
	print("obj = " + obj);

	return true;
}

private bool TestCase3() const {
	print("TestCase 3");

	NonConstMethod();

	return false;
}

private bool NonConstMethod() modify {
	return false;
}

