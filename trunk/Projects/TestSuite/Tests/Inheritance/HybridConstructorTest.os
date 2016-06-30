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
	public void DerivedObject() {
		print("DerivedObject()");
		print("mValue = " + mValue);

		base.BaseObject(5);
	}

	public void ~DerivedObject() {
		print("mValue = " + mValue);
		print("~DerivedObject()");
	}
}

public object Main {
	public void Main(int argc = 0, string argv = "") {
		DerivedObject derived = new DerivedObject();
		assert(derived);
	}
}

