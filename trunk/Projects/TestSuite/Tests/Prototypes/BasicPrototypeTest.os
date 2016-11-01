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
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1: basic prototype");

	Prototype<int> proto = new Prototype<int>(173);
	print(string proto.getValue());

	assert( proto.getValue() == 173 );
	return proto.getValue() == 173;
}
