#!/usr/local/bin/oscript

private namespace TestSpace {

	private object TestObject {
		private int mValue;

		public void Constructor(int value) {
			mValue = value;
		}

		public string ToString() const {
			return string mValue;
		}
	}

}

private object AnotherObject {
	private TestSpace.TestObject mObject;

	public void Constructor(int value) {
		mObject = new TestSpace.TestObject(value);
	}

	public TestSpace.TestObject getObject() const {
		return mObject;
	}

	public void setObject(TestSpace.TestObject obj ref) modify {
		print("setObject(" + obj.ToString() + ")");

		print("mObject vs obj = " + mObject.ToString() + " vs " + obj.ToString());
		mObject = obj;
		print("mObject vs obj = " + mObject.ToString() + " vs " + obj.ToString());
	}

	public string ToString() const {
		return "mObject = " + mObject.ToString();
	}
}

public void Main(int argc, string args) {
	AnotherObject obj = new AnotherObject(1);

	print(obj.ToString());

	TestSpace.TestObject testObj = new TestSpace.TestObject(173);
	obj.setObject(testObj);
}

