#!/usr/local/bin/oscript

import System.Integer;

public object Prototype<T> {
	private T mValue;

	public void Constructor() {
		mValue = 0;
	}

	public void Constructor(T value) {
		mValue = value;
	}

	public T getValue() const {
		return mValue;
	}

	public void setValue(T value) modify {
		mValue = value;
	}
}

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
}

public bool TestCase1() {
	print("TestCase 1: this will fail");

	print("Prototype<string> vs Prototype<int>");
	Prototype<string> proto = new Prototype<int>(173);

	assert(!"we should never get here");
	return false;
}

