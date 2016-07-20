#!/usr/local/bin/oscript

private namespace TestSpace {

private object TestObject {
	private int mValue;

	public void TestObject(int value) {
		mValue = value;
	}

	public string ToString() const {
		return string mValue;
	}
}

}

private object AnotherObject {
	private TestSpace.TestObject mObject;

	public void AnotherObject(int value) {
		mObject = new TestSpace.TestObject(value);
	}

	public TestSpace.TestObject getObject() const {
		return mObject;
	}

	public string ToString() const {
		return "mObject = " + mObject.ToString();
	}
}

public object Main {
	public void Main(int argc, string args) {
		AnotherObject obj = new AnotherObject(1);

		print(obj.ToString());

		TestSpace.TestObject obj2 = obj.getObject();
	}
}

