#!/usr/local/bin/oscript

private object Prototype<T> {
	public T mValue;

	public void Constructor(T value) {
		mValue = value;
	}
}

public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() {
	print("TestCase 1: type inference with atomic types");

	var value = 173;
	print("value = " + value);

	return value == 173;
}

private bool TestCase2() {
	print("TestCase 2: type inference with prototypes");

	var proto = new Prototype<int>(173);
	print("proto.mValue = " + proto.mValue);

	return true;
}

