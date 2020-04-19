#!/usr/local/bin/slang

private object TestObject {
	private int mValue;

	public void Constructor(int value) {
		this.mValue = value;
	}

	public int getValue() const {
		return this.mValue;
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	TestObject obj = new TestObject(1389);

	return obj.getValue() == 1389;
}

