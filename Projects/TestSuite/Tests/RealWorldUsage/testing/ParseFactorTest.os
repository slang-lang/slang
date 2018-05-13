#!/usr/local/bin/oscript

private object ComplexType {
	public int mValue = 1;

	public ComplexType operator*(int other) modify {
		print("operator*(" + other + ")");

		mValue *= other;

		return this;
	}
}

public void Main(int argc, string args) {
	print("Atomic type:");

	int value = 1 + 2;
	print("value = " + value);


	print("Complex type:");

	var obj = new ComplexType();

	print("obj.mValue = " + obj.mValue);
	obj = obj * 2;
	print("obj.mValue = "+ obj.mValue);	
}

