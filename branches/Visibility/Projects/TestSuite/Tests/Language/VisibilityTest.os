#!/usr/local/bin/oscript

private object TestObject {
	public int mPublicValue;
	protected int mProtectedValue;
	private int mPrivateValue;

	public void publicPrint() {
		print("public");
	}

	protected void protectedPrint() {
		print("protected");
	}

	private void privatePrint() {
		print("private");
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

private bool TestCase1() {
	print("TestCase 1: public read/write");

	TestObject obj = new TestObject();

	obj.mPublicValue = 1;

	obj.publicPrint();

	return true;
}

private bool TestCase2() {
	print("TestCase 2: protected read/write");

	TestObject obj = new TestObject();

	obj.mProtectedValue = 2;

	obj.protectedPrint();

	return false;
}

private bool TestCase3() {
	print("TestCase 3: private read/write");

	TestObject obj = new TestObject();

	obj.mPrivateValue = 3;

	obj.privatePrint();

	return false;
}

