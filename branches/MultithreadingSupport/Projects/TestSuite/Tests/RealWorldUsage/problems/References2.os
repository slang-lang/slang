#!/usr/local/bin/oscript

private object TestObject {
	public int mValue;

	public void Constructor(int value ref) {
		print("TestObject(value = " + value + ")");

		mValue = value;
		value += 1;
	}

	public TestObject operator+(int value) modify {
		mValue += value;

		return this;
	}

	public string =operator(string none) const {
		return string mValue;
	}
}

public void Main(int argc, string args) {
	int a ref = new int(173);

	TestObject i = new TestObject(a);

	print("a = " + string a);
	print("i = " + string i);

	CallMethod(i);

	print("a = " + string a);
	print("i = " + string i);
}

private void CallMethod(TestObject i ref) const {
	print("CallMethod(" + (string i) + ")");

	i += 1;
}

