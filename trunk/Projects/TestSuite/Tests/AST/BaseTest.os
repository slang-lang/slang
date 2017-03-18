#!/usr/local/bin/oscript

private object BaseObject {
	protected int mValue;

	public void Constructor(int value) {
		mValue = value;
	}
}

private object DerivedObject {
	private int mValue;

	public void Constructor(int value) {
		//base.Constructor(value + 1);

		mValue = value;
	}

	public string =operator(string none) const {
		return string (mValue + base.mValue);
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() modify {
	DerivedObject derived = new DerivedObject(173);

	print("derived = " + string derived);
}

