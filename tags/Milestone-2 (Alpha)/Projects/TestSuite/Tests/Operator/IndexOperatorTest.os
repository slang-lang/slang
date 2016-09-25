#!/usr/local/bin/oscript

private object TestObject {
	public int operator[(int index) const {
		return index;
	}
}

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
	}

	private bool TestCase1() const {
		int intArray[];
		intArray[5] = 173;

		int result = intArray[5];

		print("intArray[5] = " + result);

		return result == 173;
	}
}

