#!/usr/local/bin/oscript

import AbstractBase;

public object AbstractImplementation extends AbstractBase {
	public void Constructor() {
		base.Constructor();
	}

	public string =operator(string none) const {
		return "mSize = " + mSize;
	}
}

public void Main(int argc, string args) {
	print("runtime");

	AbstractImplementation impl = new AbstractImplementation();

	print(string impl.size());
}

