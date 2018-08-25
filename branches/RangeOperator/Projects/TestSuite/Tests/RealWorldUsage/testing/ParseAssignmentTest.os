#!/usr/local/bin/oscript

private object ComplexType {
	public int mValue = 1;

	public void Constructor(int value) {
		mValue = value;
	}

	public ComplexType operator=(ComplexType other const) modify {
		print("operator=(ComplexType)");
		mValue = other.mValue;

		return this;
	}

	public ComplexType operator=(Object other const) modify {
		print("operator=(Object)");

		var ct = ComplexType other;
		mValue = ct.mValue;

		return this;
	}

	public ComplexType operator=(int other) modify {
		print("operator=(int)");
		mValue = other;

		return this;
	}

	public ComplexType operator+(int other) modify {
		print("operator+(" + other + ")");

		mValue += other;

		return this;
	}
}

public void Main(int argc, string args) {
	print("Atomic type:");

	int value = 1;
	print("value = " + value);
	value += 2;
	print("value = " + value);


	print("Complex type:");

	var ct = new ComplexType();
	ct = Object new ComplexType(2);

	print("ct.mValue = " + ct.mValue);
	ct += 2;
	print("ct.mValue = " + ct.mValue);
}

