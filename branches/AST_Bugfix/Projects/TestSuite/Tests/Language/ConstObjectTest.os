#!/usr/local/bin/oscript

private stable abstract object ValueObject const {
	private int mValue;

	public void Constructor(int value) {
		mValue = value;
	}

	public bool =operator(bool none) const {
		return bool mValue;
	}
	public double =operator(double none) const {
		return double mValue;
	}
	public float =operator(float none) const {
		return float mValue;
	}
	public int =operator(int none) const {
		return mValue;
	}
	public string =operator(string none) const {
		return string mValue;
	}

	public void setValue(int value) modify {
		mValue = value;
	}
}

private object DerivedValueObject extends ValueObject {
}

public void Main(int argc, string args) {
	ValueObject value = new ValueObject(173);

	print("value = " + string value);

	value.setValue(1389);

	print("value = " + string value);
}

