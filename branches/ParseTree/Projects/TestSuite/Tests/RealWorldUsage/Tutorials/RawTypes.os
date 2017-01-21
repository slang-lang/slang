#!/usr/local/bin/oscript

import System.Integer;

private object Box<T> {
	public int mId;
	public T mValue;

	public void Constructor(int id) {
		mId = id;
	}

	public void set(T value) {
		mValue = value;
	}

	public string =operator(string none) const {
		return string mId;
	}
}

public void Main(int argc, string args) {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1: raw type");

	Box<Integer> integerBox = new Box<Integer>(1);
	assert( integerBox );

	Box rawBox = new Box(2);
	assert( rawBox );

	assert( (string integerBox) < (string rawBox) );
	print("(string integerBox) < (string rawBox)");

	return true;
}

