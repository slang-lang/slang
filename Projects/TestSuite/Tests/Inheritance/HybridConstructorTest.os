#!/usr/local/bin/slang

private object BaseObject {
	protected int mValue;

	public void Constructor(int value) {
		print("Constructor(" + value + ")");

		mValue = value;
	}

	public void Destructor() {
		print("Destructor(" + mValue + ")");
	}

	public int getValue() const {
		return mValue;
	}
}

private object DerivedObject extends BaseObject {
	private int mValue;

	public void Constructor() {
		print("Constructor()");
		print("mValue = " + mValue);
		print("base.getValue() = " + base.getValue());

		base.Constructor(5);

		print("mValue = " + mValue);
		print("base.getValue() = " + base.getValue()); 
	}

	public void Destructor() {
		print("Destructor()");
		print("mValue = " + mValue);
		print("base.getValue() = " + base.getValue()); 
	}

	public int getValue() const {
		return mValue;
	}
}

public void Main(int argc = 0, string argv = "") {
	DerivedObject derivedObj = new DerivedObject();
	assert(derivedObj);
}

