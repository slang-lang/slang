#!/usr/local/bin/oscript

private object TestObject {
	private int mValue;

	private void TestObject(int value) {
		mValue = value;
	}

	public string ToString() const {
		return "TestObject={ mValue=" + mValue + " }";
	}

	public bool operator==(int other) const {
		print("operator==(int)");
		return mValue == other;
	}
	public bool operator==(TestObject other) const {
		print("operator==(TestObject)");
		return mValue == other.mValue;
	}

	public void operator=(int other) modify {
		print("operator=(int)");
		mValue = other;
	}

	public int =operator() const {
		print("int =operator()");
		return mValue;
	}

	public void operator++() modify {
		print("operator++");
		mValue = mValue++;
	}

	public void ++operator() modify {
		print("++operator");
		mValue = mValue++;
	}
}

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() const {
		print("TestCase 1: classic operator");

		TestObject obj = new TestObject(1);
		print(obj.ToString());

		obj++;

		print(obj.ToString());

		return true;
	}

	private bool TestCase2() const {
		print("TestCase 2: modern operator");

		TestObject obj = new TestObject(1);
		print(obj.ToString());

		obj=++obj;

		print(obj.ToString());

		return true;
	}
}
