#!/usr/local/bin/oscript

public object ComplexType {
	public int mValue;

	public ComplexType operator=(int value) modify {
		print("operator=(int)");
		mValue = value;

		return this;
	}

	public ComplexType operator=(ComplexType other modify) modify {
		print("operator=(ComplexType)");

		mValue = other.mValue;

		return this;
	}

	public void modifiableParameter(ComplexType other modify) modify {
		print("modifiableParameter(ComplexType)");
	}
}

public void Main(int argc, string args) {
	print("Atomic type:");

	int value = 173;
	print("value = " + value);


	print("Complex type:");

	var ct const = new ComplexType();
	print("ct.mValue = " + ct.mValue);

	ComplexType obj = ct;
	obj.modifiableParameter(ct);
}

