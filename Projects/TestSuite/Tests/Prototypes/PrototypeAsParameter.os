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

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );		// not supported by now
}

private bool TestCase1() {
	print("TestCase 1: method with prototype as parameter");

	Prototype<int> proto = new Prototype<int>(173);
	print(string proto.getValue());

	return MethodWithPrototypeParameter(proto);
}

private bool MethodWithPrototypeParameter(Prototype<int> proto) {
	return proto.getValue() == 173;
}

