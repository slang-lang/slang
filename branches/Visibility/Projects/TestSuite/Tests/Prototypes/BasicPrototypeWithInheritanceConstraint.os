#!/usr/local/bin/oscript

import System.Integer;
import System.String;

public prototype Prototype<T: Object> {
	private T mValue;

	public void Constructor(T value) {
		print("Prototype<T>.Constructor(" + value + ")");

		mValue = value;
	}

	public T getValue() const {
		return mValue;
	}

	public void doIt() {
		T value = mValue;

		print("value = " + value);
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );	// success
	assert( TestCase2() );	// fail
}

private bool TestCase1() {
	print("TestCase 1: basic prototype");

	Prototype<Integer> proto = new Prototype<Integer>(173);
	print("proto.getValue() = " + proto.getValue());

	proto.doIt();

	assert( proto.getValue() == 173 );
	return proto.getValue() == 173;
}

private bool TestCase2() {
	print("TestCase 2: constraint type fail");

	Prototype<int> proto = new Prototype<int>(173);

	assert(!"this should not be possible");
	return false;
}

