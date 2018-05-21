#!/usr/local/bin/oscript

private object ComplexType {
	public int mValue = 1;

	public bool operator==(int other) modify {
		print("operator==(" + other + ")");

		return mValue == other;
	}
}

public void Main(int argc, string args) {
	print("Atomic type:");

	int value = 1 + 2;
	print("value = " + value);


	print("Complex type:");

	var ct = new ComplexType();

	print("ct.mValue = " + ct.mValue);
	if ( ct == 1 ) {
		print("ct == 1");
	}
	else {
		print("ct != 1");
	}

	if ( ct != 2 ) {
		print("ct != 2");
	}
	else {
		print("ct == 2");
	}
}

