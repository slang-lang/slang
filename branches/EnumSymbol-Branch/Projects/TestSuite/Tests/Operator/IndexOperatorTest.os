#!/usr/local/bin/oscript

private object TestObject {
	public int operator[](int index) const {
		return index;
	}
}

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
	}

	private bool TestCase1() const {
		TestObject obj = new TestObject();

		int result = obj[5];

		print("obj[5] = " + result);

		return result == 5;
	}
}

