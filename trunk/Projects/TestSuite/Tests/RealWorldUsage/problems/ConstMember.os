#!/usr/local/bin/oscript

private object ConstMember const {
	public int mValue const;

	public void Constructor(int value) {
		mValue = value;

/*
		int v const = 17;
		v = 18;
*/
	}
}

public void Main(int argc, string args) {
	ConstMember c = new ConstMember(173);

	c.mValue++;
	c.mValue = 1389;

	print("c.mValue = " + c.mValue);
}

