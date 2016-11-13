#!/usr/local/bin/oscript

private namespace Space {
	private object TestObject {
		public int mConstValue const = 1389;
		public int mMutableValue modify = -173;

		public void Constructor() {
			print("mConstValue = " + mConstValue);
			print("mMutableValue = " + mMutableValue);
		}
	}
}

private int mNumber = -173;
private Space.TestObject mTestObject;

private Space.TestObject createTestObject() const {
	return new Space.TestObject();
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() const {
	Space.TestObject obj1 = createTestObject();

	mTestObject = createTestObject();
	mTestObject.mMutableValue = 664;

	return obj1.mMutableValue == -173;
}

