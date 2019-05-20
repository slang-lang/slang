#!/usr/local/bin/oscript

object TestObject {
	public void Constructor(Object value const) {
		mValue = value;

		assert( !"this is wrong!" );
	}

/*
	public void setValue(Object value const) {
		mValue = value;

		assert( !"this is wrong!" );
	}
*/

	private Object mValue;
}

public void Main(int argc, string args) {
	TestObject obj = new TestObject( new Object() );
}

