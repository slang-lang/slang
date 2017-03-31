#!/usr/local/bin/oscript

// THIS WILL FAIL

public object ForwardObject;

public object ForwardObject {
	public int mValue;

	public void Constructor(int value) {
		mValue = value;
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() const {
	print("TestCase 1: object declaration after forward declaration");

	ForwardObject obj = new ForwardObject(173);
	assert(obj);

	print(obj.mValue);

	return true;
}

