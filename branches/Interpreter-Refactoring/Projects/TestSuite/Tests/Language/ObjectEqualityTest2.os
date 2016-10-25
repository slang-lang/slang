#!/usr/local/bin/oscript

public namespace ObjectEqualityTest {
	private object TestObject {
		private int mValue;

		public int getValue() const {
			return mValue;
		}

		public string ToString() const {
			return "TestObject { mValue = " + mValue + " }";
		}
		public string =operator(string none) const {
			return "TestObject { mValue = " + mValue + " }";
		}

		public void operator=(TestObject other const ref) modify {
			print("operator=(" + other.ToString() + ")");
			mValue = value;
		}

		public bool operator==(TestObject other const ref) const {
			print("operator==(" + other.ToString() + ")");
			return mValue == other.mValue;
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
	//obj1.mValue = 1;
	ObjectEqualityTest.TestObject obj2 = new ObjectEqualityTest.TestObject();
	//obj2.mValue = 2;
	
	return obj1 == obj2;
}

private bool TestCase2() const {
	print("TestCase 2: comparing same references");

	ObjectEqualityTest.TestObject obj1 = new ObjectEqualityTest.TestObject();
	obj1.mValue = 1;
	ObjectEqualityTest.TestObject obj2 = obj1;
	obj2.mValue = 2;

	return obj1 == obj2;
}

