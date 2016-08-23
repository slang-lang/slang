#!/usr/local/bin/oscript

public object ForwardObject;

public object ForwardObject {
	private int mValue;

	public void ForwardObject(int value) {
		mValue = value;
	}
}

public object Main {
	public void Main(int argc = 0, string args = "") {
		ForwardObject obj = new ForwardObject(173);
		assert(obj);
	}
}

