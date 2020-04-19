#!/usr/local/bin/slang

public object Prototype<T> {
	private T mValue;

	public void Constructor(T value) {
		print("Prototype<T>.Constructor(" + value + ")");

		mValue = value;
	}

	public T getValue() const {
		return mValue;
	}

	public void doIt() {
		T value const = mValue;

		print("value = " + value);
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1: basic prototype");

	Prototype<int> proto = new Prototype<int>(173);
	print("proto.getValue() = " + proto.getValue());

	proto.doIt();

	assert( proto.getValue() == 173 );
	return proto.getValue() == 173;
}
