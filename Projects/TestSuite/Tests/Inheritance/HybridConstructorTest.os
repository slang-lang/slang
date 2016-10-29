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
	private int mValue;

	public void Constructor() {
		print("Constructor()");
		print("mValue = " + mValue);
		print("base.mValue = " + base.mValue);

		base.Constructor(5);

		print("mValue = " + mValue);
		print("base.mValue = " + base.mValue);
	}

	public void Destructor() {
		print("mValue = " + mValue);
		print("base.mValue = " + base.mValue);
		print("Destructor()");
	}
}

public void Main(int argc = 0, string argv = "") {
	DerivedObject derived = new DerivedObject();
	assert(derived);
}

