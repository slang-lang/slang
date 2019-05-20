#!/usr/local/bin/oscript

import System.String;

object TestObject {
	public String mValue;

	public void Constructor(String value const) {
		mValue = value;

		assert( !"this is wrong!" );
	}

	public void setValue(String value const) {
		mValue = value;

		assert( !"this is wrong!" );
	}
}

public void Main(int argc, string args) {
	TestObject obj = new TestObject( new String("bla") );
}

