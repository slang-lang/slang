#!/usr/local/bin/oscript

public object TestObject {
	private int mValue;

	public void Constructor(int value) {
		print("Constructor(" + value + ")");
		mValue = value;
	}

	public void Destructor() {
		print("Destructor()");
	}
}

public void Main(int argc, string args) {
	TestObject obj = new TestObject(173);

	print(obj.mValue);
	obj = null;

	print(obj);
	assert(!obj);
}

