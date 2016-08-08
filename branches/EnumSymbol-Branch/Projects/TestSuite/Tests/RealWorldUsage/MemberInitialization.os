#!/usr/local/bin/oscript

private object TestObject {
	private int mConstValue = 1389;
	private int mMutableValue = 173;

	public void TestObject() {
		print("mConstValue = " + mConstValue);
		print("mMutableValue = " + mMutableValue);
	}
}

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
	}

	private bool TestCase1() const {
		TestObject obj1 = new TestObject();

		return obj1.mMutableValue == 173;
	}
}

