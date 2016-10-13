#!/usr/local/bin/oscript

private object BaseObject {
	protected int mValue;

	public void BaseObject(int value) {
		print("BaseObject(" + value + ")");

		mValue = value;
	}

	public void ~BaseObject() {
		print("~BaseObject(" + mValue + ")");
	}
}

private object DerivedObject extends BaseObject {
	private int mValue;

	public void DerivedObject() {
		print("DerivedObject()");
		print("mValue = " + mValue);
		print("base.mValue = " + base.mValue);

		base.BaseObject(5);

		print("mValue = " + mValue);
		print("base.mValue = " + base.mValue);
	}

	public void ~DerivedObject() {
		print("mValue = " + mValue);
		print("base.mValue = " + base.mValue);
		print("~DerivedObject()");
	}
}

public void Main(int argc = 0, string argv = "") {
	DerivedObject derived = new DerivedObject();
	assert(derived);
}

