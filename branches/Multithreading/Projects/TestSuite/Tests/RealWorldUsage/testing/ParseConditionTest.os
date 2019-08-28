#!/usr/local/bin/oscript

private object ComplexType {
	public int mValue = 1;

	public void Constructor(int value) {
		mValue = value;
	}

	public bool operator==(int other) const {
		print("operator==(" + other + ")");

		return mValue == other;
	}

	public bool operator==(ComplexType other const) const {
		print("operator==(ComplexType)");

		return mValue == other.mValue;
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

	var ct2 = new ComplexType(2);
	assert( ct != ct2 );
}

