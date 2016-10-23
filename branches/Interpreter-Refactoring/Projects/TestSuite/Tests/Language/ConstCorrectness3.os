#!/usr/local/bin/oscript

private object UserObject {
	private int mValue;

	public void UserObject(int value) {
		mValue = value;
	}

	public void ~UserObject() {
	}

	public int getValue() const {
		return mValue;
	}

	public void setValue(int value const) modify {
		mValue = value;
	}
}

public void Main(int argc = 0, string argv = "") {
	//assert( ObjectAsReference() );
	assert( ObjectAsConstReference() );
}

private bool ObjectAsConstReference() const {
	print("ObjectAsConstReference()");

	// altough all objects are references it should never be possible to change a const object => fail

	UserObject obj1 = new UserObject(1);

	UpdateConstUserObject(obj1);

	print("He's dead, Jim");

	// we should not get here
	obj1.setValue(3);

	assert(!"this test has to fail!");
	return false;
}

private bool ObjectAsReference() const {
	print("ObjectAsReference()");

	// all objects are references so this is perfectly valid => success

	UserObject obj1 = new UserObject(1);

	UpdateUserObject(obj1);

	assert( obj1.getValue() == 2 );

	obj1.setValue(3);

	return true;
}

private bool UpdateConstUserObject(UserObject objConstRef const ref) const {
	// altough all objects are references it should never be possible to change a const object => fail
	objConstRef.setValue(2);

	return false;
}

private bool UpdateUserObject(UserObject objRef ref) const {
	// all objects are references so this is perfectly valid => success

	objRef.setValue(2);

	return true;
}

