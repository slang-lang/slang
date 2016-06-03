#!/usr/local/bin/oscript

private object TestObject {
	public int getValue() const {
		assert(false);
		return "bla";
	}

	public string =operator(string value) const {
		return "TestObject";
	}
}

public object Main {
	public void Main(int argc, string argv) {
		assert( TestCase1() );
		assert( TestCase2() );
		assert( TestCase3() );
	}

	private bool TestCase1() const {
		print("TestCase 1: bool(true)");

		bool value = true;
		print("value = " + value);

		value!;

		return true;
	}

	private bool TestCase2() const {
		print("TestCase 2: TestObject(null)");

		try {
			TestObject obj;
			print(obj!);
			obj!.getValue();

			assert(!"obj validation failed");
		}
		catch {
			print("caught validation exception");
			return true;
		}

		return false;
	}

	private bool TestCase3() const {
		print("TestCase 3: int(0)");

		try {
			int value;
			print("value = " + value);

			value!;
		}
		catch {
			print("caugth validation exception");
			return true;
		}

		return false;
	}
}

