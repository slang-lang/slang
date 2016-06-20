#!/usr/local/bin/oscript

private object TestObject {
	private int mValue;

	public int getValue() const {
		return mValue;
	}

	public void setValue(int value) modify {
		mValue = value;
	}

	public void operator=(int value) modify {
		mValue = value;
	}

	public int operator=() const {
		return mValue;
	}

	public void operator+(int value) modify {
		mValue = mValue + value;
	}
}

private object DerivedObject extends TestObject {
	public void setValue(int value) modify {
		//mValue = value * value;
		operator=(value);	// this is really caarazy but it only works if it is called from the inside of an object
		operator+(5);

		writeln("operator=() = " + string operator=());
	}

	public void operator=(int value) modify {
		mValue = value * value;
	}
}

private object Retyped replicates TestObject;

/*
private prototype Proto<value>
{
}

private object RetypedProto replicates Proto<int>;
*/

private object Main {
	public void Main(int argc, string argv) {
		DerivedObject derived;
		print("derived.getValue() = " + derived.getValue());
		derived.setValue(2);
		print("derived.getValue() = " + derived.getValue());
		derived = 3;
		print("derived.getValue() = " + derived.getValue());

		Retyped retyped;
		print("retyped.getValue() = " + retyped.getValue());
		retyped.setValue(2);
		print("retyped.getValue() = " + retyped.getValue());
		retyped = 3;
		print("retyped.getValue() = " + retyped.getValue());
	}
}

