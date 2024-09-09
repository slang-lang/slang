#!/usr/local/bin/slang

private object TestObject {
	public int getValue() const {
		assert(false);
		return 0;
	}

	public string =operator(string value) const {
		return "TestObject";
	}
}

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
	assert( TestCase2() );
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
		return cast<bool>( obj!.getValue() );

		assert(!"obj validation failed!");
	}
	catch {
		print("SUCCESS: caught validation exception");
		return true;
	}

	return false;
}

