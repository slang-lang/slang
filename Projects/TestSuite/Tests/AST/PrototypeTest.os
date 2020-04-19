#!/usr/local/bin/slang

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

	public void operator=(TestObject<T> other const ref) modify {
		mValue = other.getValue();
	}
}

public void Main(int argc, string args) {
	TestObject<int> obj1 = new TestObject<int>(173);
	print("obj1 = " + obj1.toString());

	TestObject<int> obj2 = new TestObject<int>(1389);
	print("obj2 = " + obj2.toString());

	obj1 = obj2;
	print("obj1 = " + obj1.toString());
}

