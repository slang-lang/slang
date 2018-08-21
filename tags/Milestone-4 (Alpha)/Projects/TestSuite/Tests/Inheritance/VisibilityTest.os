#!/usr/local/bin/oscript

private object BaseObject {
	public int mPublicValue;
	protected int mProtectedValue;
	private int mPrivateValue;
}

private object DerivedObject extends BaseObject {
	public void Constructor() {
		mPublicValue = 1;
		mProtectedValue = 2;
		mPrivateValue = 3;
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1: read/write parent members");

	DerivedObject derived = new DerivedObject();

	return false;
}

