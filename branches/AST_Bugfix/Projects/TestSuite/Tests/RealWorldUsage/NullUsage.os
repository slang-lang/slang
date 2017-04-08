#!/usr/local/bin/oscript

public object TestObject {
	public int mValue;

	public void Constructor(int value) {
		print("Constructor(" + value + ")");
		mValue = value;
	}

	public void Destructor() {
		print("Destructor()");
	}

	public string =operator(string none) const {
		return string mValue;
	}
}

public void Main(int argc = 0, string args = "") {
	TestObject obj = new TestObject(173);
	print(obj.mValue);

	obj = TestObject null;
	// obj should not be accessible any more

	print(string obj);
	assert(!obj);
}

