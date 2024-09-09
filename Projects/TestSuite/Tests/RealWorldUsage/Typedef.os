#!/usr/local/bin/slang

private object TestObject {
	protected int mValue;

	public int getValue() const {
		return mValue;
	}

	public void setValue(int value) modify {
		mValue = value;
	}

	public TestObject operator=(int value) modify {
		mValue = value;

		return this;
	}

	public int =operator(int none) const {
		return mValue;
	}

	public TestObject operator+(int value) modify {
		mValue = mValue + value;

		return this;
	}
}

private object DerivedObject extends TestObject {
	public void setValue(int value) modify {
		//mValue = value * value;
		operator=(value);	// this is really caarazy but it only works if it is called from the inside of an object
		operator+(5);
	}

	public DerivedObject operator=(int value) modify {
		mValue = value * value;

		return this;
	}
}

//private object Retyped replicates TestObject;
private object Retyped extends TestObject;

public void Main(int argc, string argv) {
	DerivedObject derived = new DerivedObject();
	print("derived.getValue() = " + derived.getValue());
	derived.setValue(2);
	print("derived.getValue() = " + derived.getValue());
	derived = 3;
	print("derived.getValue() = " + derived.getValue());

	Retyped retyped = new Retyped();
	print("retyped.getValue() = " + retyped.getValue());
	retyped.setValue(2);
	print("retyped.getValue() = " + retyped.getValue());
	retyped = 3;
	print("retyped.getValue() = " + retyped.getValue());
}

