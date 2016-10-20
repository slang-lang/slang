#!/usr/local/bin/oscript

private namespace Space {
	private object TestObject {
		private int mConstValue = 1389;
		private int mMutableValue = 173;

		public void TestObject() {
			print("mConstValue = " + mConstValue);
			print("mMutableValue = " + mMutableValue);
		}
	}
}

private int mNumber = 173;
private Space.TestObject mTestObject;

private Space.TestObject createTestObject() const {
	return new TestObject();
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() const {
	Space.TestObject obj1 = new Space.TestObject();

	return obj1.mMutableValue == 173;
}

