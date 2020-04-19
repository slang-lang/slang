#!/usr/local/bin/slang

private object TestObject {
	private int mValue;

	public void Constructor(int value) {
		this.mValue = value;
	}

	public string =operator(string none) const {
		return string mValue;
	}

	public int getValue() const {
		return (mValue)++;
	}
}

public void Main(int argc = 0, string args = "") {
	TestObject obj = new TestObject(173);

	print(string obj);

	print("mValue = " + obj.getValue());
	print("mValue = " + obj.getValue());
}

