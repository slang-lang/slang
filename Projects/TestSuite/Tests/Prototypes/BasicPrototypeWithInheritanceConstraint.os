#!/usr/bin/env slang

import System.Integer;
import System.String;

public object Prototype<T: Object> {
	private T mValue;

	public void Constructor(T value) {
		print("Prototype<" + typeid(value) + ">.Constructor(" + (string value) + ")");

		mValue = value;
	}

	public T getValue() const {
		return mValue;
	}

	public void doIt() {
		T value = mValue;

		print("value = " + string value);
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );	// success
}

private bool TestCase1() {
	print("TestCase 1: basic prototype");

	Prototype<Integer> proto = new Prototype<Integer>(new Integer(173));
	print("proto.getValue() = " + string proto.getValue());

	proto.doIt();

	assert( proto.getValue() == 173 );
	return proto.getValue() == 173;
}

