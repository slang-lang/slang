#!/usr/local/bin/oscript

private object TestObject {
/*
	public void TestObject(int value)
	{
	}
*/

	public int getValue() const {
		assert(false);
		return "bla";
	}
}

public object Main {
	public void Main(int argc, string argv) {
		assert( TestCase1() );
		assert( TestCase2() );
		assert( TestCase3() );
	}

	private bool TestCase1() const {
		print("TestCase 1");

		bool value = true;

		value!;

		return true;
	}

	private bool TestCase2() const {
		print("TestCase 2");

		try {
			TestObject obj;
			obj!.getValue();

			assert(!"obj validation failed");
		}
		catch {
		}

		return true;
	}

	private bool TestCase3() const {
		print("TestCase 3");

		int value = 0;

		value!;

		return false;
	}
}

