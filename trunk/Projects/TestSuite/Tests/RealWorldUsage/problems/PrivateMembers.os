#!/usr/local/bin/oscript

object BaseObject {
	private int mValue = 173;

	public int getValue() const {
		return mValue;
	}
}

object DerivedObject extends BaseObject {
	public int getBaseValue() const {
		return base.getValue();
	}
}

public void Main(int argc, string args) {
	var derived = new DerivedObject();

	print(string derived.getBaseValue());
}

