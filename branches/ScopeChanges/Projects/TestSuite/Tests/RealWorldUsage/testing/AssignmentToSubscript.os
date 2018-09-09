#!/usr/local/bin/oscript

public object SubscriptObject {
	public int mValue;

	public int operator[](int value) const {
		print("operator[](int)");

		return mValue;
	}

	public SubscriptObject operator=(int value) modify {
		print("operator=(int)");
		mValue = value;

		return this;
	}

	public SubscriptObject operator=(SubscriptObject other const) modify {
		print("operator=(SubscriptObject)");
		mValue = other.mValue;

		return this;
	}
}

public void Main(int argc, string args) {
	SubscriptObject obj = new SubscriptObject();

	obj[0] = 1;
}

