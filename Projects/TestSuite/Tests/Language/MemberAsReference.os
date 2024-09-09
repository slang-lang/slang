#!/usr/local/bin/slang

private object TestObject {
	private int mValue ref;

	public void Constructor(int value ref) {
		mValue = value;
	}

	public int getValue() const {
		return mValue;
	}

	public string =operator(string none) const {
		return string mValue;
	}
}

public void Main(int argc, string args) {
	int value ref = new int(0);

	TestObject obj = new TestObject(value);
	print("obj = " + string obj);
	print("value = " + value);

	value++;

	print("obj = " + string obj);
	print("value = " + value);
}

