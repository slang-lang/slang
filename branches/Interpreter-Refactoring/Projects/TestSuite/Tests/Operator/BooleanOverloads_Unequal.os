#!/usr/local/bin/oscript

private namespace BooleanOverloads {
	private object UserObject {
		private int mValue;

		public void Constructor(int value const) {
			mValue = value;
		}

		public int GetValue() const {
			return mValue;
		}

		public bool operator==(int value const) const {
			return mValue == value;
		}
	}
}

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase1: unequal operator with atomic type");

	BooleanOverloads.UserObject obj1 = new BooleanOverloads.UserObject(1);
	assert( obj1 == 1 );

	if ( obj1 != 2 ) {
		print("obj1 != 2");
		return true;
	}

	return false;
}

private bool TestCase2() const {
	print("TestCase2: unequal operator with object");

	BooleanOverloads.UserObject obj1 = new BooleanOverloads.UserObject(1);
	assert( obj1 == 1 );
	BooleanOverloads.UserObject obj2 = new BooleanOverloads.UserObject(2);
	assert( obj2 == 2 );

	if ( obj1 != obj2 ) {
		print("obj1 != obj2");
		return true;
	}

	return false;
}

