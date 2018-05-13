#!/usr/local/bin/oscript

private object UnaryDecrement {
	public int mValue = 0;

	public UnaryDecrement operator--() modify {
		print("operator--()");
		mValue--;

		return this;
	}

	public UnaryDecrement operator++() modify {
		print("operator++()");
		mValue++;

		return this;
	}
}

public void Main(int argc, string args) {
	print("Atomic type:");

	int value = 0;

	print("value: " + value);
	value--;
	print("value: " + value);


	print("Complex type:");

	var obj = new UnaryDecrement();

	print("obj.mValue: " + obj.mValue);
	obj--;
	print("obj.mValue: " + obj.mValue);
}

