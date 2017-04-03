#!/usr/local/bin/oscript

private object TestObject<T> {
	private T mValue;

	public void Constructor(T value) {
		mValue = value;
	}

	public T getValue() const {
		return mValue;
	}
	public void setValue(T value) modify {
		mValue = value;
	}

	public string toString() const {
		return string mValue;
	}
}

public void Main(int argc, string args) {
	TestObject<int> obj = new TestObject<int>(173);

	print("obj = " + obj.toString());
}

