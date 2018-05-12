#!/usr/local/bin/oscript

private object UserObject {
	private int mValue;

	public void Constructor(int value const) {
		print("Constructor(" + value + ")");
		mValue = value;
	}

	public int getValue() const {
		print("getValue()");
		return mValue;
	}

	public void setValue(int value const) modify {
		print("setValue(" + value + ")");
		mValue = value;
	}

	/////////////////////////////////////////////////////////////////////

	public void operator=(int other const) modify {
		print("operator=(int)");
		mValue = other;
	}

	public void operator=(UserObject other const) modify {
		print("operator=(UserObject)");
		mValue = other.getValue();
	}

	public bool operator==(int other const) const {
		print("operator==(int)");
		return mValue == other;
	}

	public bool operator==(UserObject other const) const {
		print("operator==(UserObject)");
		return mValue == other.getValue();
	}

	public string ToString() const {
		return (string mValue);
	}
}


public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase1: assign operator with atomic type");

	UserObject obj1 = new UserObject(1);

	obj1 = 2;
	print("obj1.getValue() = " + obj1.getValue());

	assert( obj1 == 2 );
	if ( obj1 == 2 ) {
		print("obj1 == 2");
		print(obj1.ToString() + " == 2");
		return true;
	}

	return false;
}

private bool TestCase2() const {
	print("TestCase2: assign operator with object");

	UserObject obj1 = new UserObject(1);
	UserObject obj2 = new UserObject(1);

	obj1 = obj2;
	assert( obj1 == obj2 );
	if ( obj1 == obj2 ) {
		print("obj1 == obj2");
		print(obj1.ToString() + " == " + obj2.ToString());
		return true;
	}

	return false;
}

