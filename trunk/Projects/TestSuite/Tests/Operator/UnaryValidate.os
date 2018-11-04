#!/usr/local/bin/oscript

private object TestObject {
	public int getValue() const {
		assert(false);
		return 0;
	}

	public string =operator(string value) const {
		return "TestObject";
	}
}

public void Main(int argc, string argv) {
	assert( TestCase1() );
	assert( TestCase2() );
	//assert( TestCase3() );
}

private bool TestCase1() const {
	print("TestCase 1: bool(true)");

	bool value = true;
	print("value = " + value);

	return value!;
}

private bool TestCase2() const {
	print("TestCase 2: TestObject(null)");

	try {
		TestObject obj;
		return bool obj!.getValue();

		assert(!"obj validation failed!");
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

		//value!;

		assert(!"int validation failed!");
	}
	catch {
		print("caught validation exception");
		return true;
	}

	return false;
}

