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
	public void DerivedObject(int value) {
		print("DerivedObject(" + value + ")");
		print("mValue = " + mValue);

		base.BaseObject(value);
	}

	public void ~DerivedObject() {
		print("mValue = " + mValue);
		print("~DerivedObject(" + mValue + ")");
	}
}

public void Main(int argc = 0, string argv = "") {
	DerivedObject derived = new DerivedObject(5);
	print("derived.mValue = " + derived.mValue);
}

