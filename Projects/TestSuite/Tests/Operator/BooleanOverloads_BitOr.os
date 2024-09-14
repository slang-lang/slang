#!/usr/local/bin/slang

private object UserObject {
	private int mValue;

	public void Constructor(int value const) {
		mValue = value;
	}

	public int getValue() const {
		return mValue;
	}

	public void setValue(int value const) modify {
		mValue = value;
	}

	/////////////////////////////////////////////////////////////////////

	public UserObject operator|(int other const) modify {
		mValue = mValue | other;

		return this;
	}

	public UserObject operator|(UserObject other const) modify {
		mValue = mValue | other.getValue();

		return this;
	}

	public bool operator==(int other const) const {
		return mValue == other;
	}

	public bool operator==(UserObject other const) const {
		return mValue == other.getValue();
	}
}

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase1: bitor operator with atomic type");

	UserObject obj1 = new UserObject(1001);

	obj1 = obj1 | 0110;
	//assert( obj1 == true );

print("obj1.getValue() = " + obj1.getValue());
return true;

	if ( obj1 ) {
		print("obj1 == true");
		return true;
	}

	return false;
}

private bool TestCase2() const {
	print("TestCase2: bitor operator with object");

	UserObject obj1 = new UserObject(1001);
	UserObject obj2 = new UserObject(0110);

	obj1 = obj1 | obj2;
	//assert( obj1 == true );

print("obj1 = " + obj1.getValue());
return true;

	if ( obj1 ) {
		print("obj1 == true");
		return true;
	}

	return false;
}

