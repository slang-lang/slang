#!/usr/local/bin/oscript

private object CopyObject {
	public int mValue;

	public void Constructor(int value) {
		mValue = value;
	}
}

public void Main(int argc, string args) {
	CopyObject obj1 = new CopyObject(173);
	CopyObject obj2 = copy obj1;
}

