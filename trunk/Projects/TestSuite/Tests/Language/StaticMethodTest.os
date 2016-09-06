#!/usr/local/bin/oscript

public object TestObject {
	private int mValue;

	public void TestObject(int value) {
		mValue = value;
	}

	public void nonstaticPrint() {
		print("nonstaticPrint: " + mValue);
	}

	public void staticPrint(bool callNonStatic = false) static {
		if ( callNonStatic ) {
			nonstaticPrint();
			return;
		}

		int value = 17;
		print("staticPrint: " + value);
	}
}

public object Main {
	public void Main(int argc, string args) {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() const {
		TestObject.staticPrint();

		return true;
	}

	private bool TestCase2() const {
		TestObject.staticPrint(true);

		return false;
	}
}

