#!/usr/local/bin/slang

public object Prototype<T> {
	private T mValue;

	public void Constructor(T value) {
		mValue = value;
	}

	public T getValue() const {
		return mValue;
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1: method with prototype as return value");

	Prototype<int> proto = new Prototype<int>(173);
	print(string proto.getValue());

	proto = MethodWithPrototypeAsReturnValue(664);

	return proto.getValue() == 664;
}

private Prototype<int> MethodWithPrototypeAsReturnValue(int value) {
	print("MethodWithPrototypeAsReturnValue(" + value + ")");

	return new Prototype<int>(value);
}

