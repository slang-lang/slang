#!/usr/local/bin/oscript

public prototype Prototype<T> {
	private T mValue;

	public void Constructor(T value) {
		mValue = value;
	}

	public T getValue() const {
		return mValue;
	}
}

public object TestObject {
	private Prototype<int> mValue;
	
	public void Constructor(int value) {
		mValue = new Prototype<int>(value);
	}
	
	public int getValue() const {
		return mValue.getValue();
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );		// not supported by now
}

private bool TestCase1() {
	print("TestCase 1: prototype as member");

	TestObject obj = new TestObject(173);

	return obj.getValue() == 173;
}
