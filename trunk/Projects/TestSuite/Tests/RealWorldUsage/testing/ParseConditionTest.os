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

	var obj = new ComplexType();

	print("obj.mValue = " + obj.mValue);
	if ( obj == 1 ) {
		print("obj == 1");
	}
	else {
		print("obj != 1");
	}

	if ( obj != 2 ) {
		print("obj != 2");
	}
	else {
		print("obj == 2");
	}
}

