#!/usr/bin/env slang

public object TestObject {
	private int mValue;

	public void Constructor(int value) {
		mValue = value;
	}

	public void nonstaticPrint() {
		print("nonstaticPrint: " + mValue);
	}

	public static void staticPrint(bool callNonStatic) {
		if ( callNonStatic ) {
			nonstaticPrint();
			return;
		}

		int value = 17;
		print("staticPrint: " + value);
	}
}

public void Main(int argc = 0 , string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	TestObject.staticPrint(false);

	return true;
}

private bool TestCase2() const {
	TestObject.staticPrint(true);

	return false;
}

