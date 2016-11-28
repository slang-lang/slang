#!/usr/local/bin/oscript

public namespace ObjectEqualityTest {
	public object TestObject {
		private int mValue;

		public int getValue() const {
			return mValue;
		}

		public void setValue(int value const) {
			mValue = value;
		}
	}
}

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase 1: comparing different references");

	ObjectEqualityTest.TestObject obj1 = new ObjectEqualityTest.TestObject();
	ObjectEqualityTest.TestObject obj2 = new ObjectEqualityTest.TestObject();
	
	return obj1 != obj2;
}

private bool TestCase2() const {
	print("TestCase 2: comparing same references");

	ObjectEqualityTest.TestObject obj1 = new ObjectEqualityTest.TestObject();
	ObjectEqualityTest.TestObject obj2 = obj1;

	return obj1 == obj2;
}

