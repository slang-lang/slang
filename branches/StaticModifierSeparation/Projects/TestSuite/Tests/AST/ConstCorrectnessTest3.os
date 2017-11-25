#!/usr/local/bin/oscript

private object TestObject {
	private int mValue;

	public void Constructor(int value) {
		mValue = value;
	}

	public int getValue() const {
		// increment mValue every time this method gets called; this has to fail!
		setValue(mValue + 1);

		return mValue;
	}
	public void setValue(int value) modify {
		mValue = value;
	}
}

public void Main(int argc = 0, string args = "") modify {
	TestObject obj = new TestObject(173);

	obj.setValue(1389);
}

