#!/usr/local/bin/oscript

private object BaseObject {
	protected int mValue;

	public void Constructor(int value) {
		print("Constructor(" + value + ")");

		mValue = value;
	}

	public void Destructor() {
		print("Destructor(" + mValue + ")");
	}
}

private object DerivedObject extends BaseObject {
	public void Constructor(int value) {
		print("Constructor(" + value + ")");
		print("mValue = " + mValue);

		base.Constructor(value);
	}

	public void Destructor() {
		print("mValue = " + mValue);
		print("Destructor(" + mValue + ")");
	}
}

public void Main(int argc = 0, string argv = "") {
	DerivedObject derived = new DerivedObject(5);
	print("derived.mValue = " + derived.mValue);
}

