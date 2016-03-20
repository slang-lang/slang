#!/usr/local/bin/oscript

private object TestObject
{
	private int mValue;

	public int getValue() const
	{
		return mValue;
	}

	public void setValue(int value) modify
	{
		mValue = value;
	}
}

private object DerivedObject extends TestObject
{
	public void setValue(int value) modify
	{
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

private object Main
{
	public void Main(int argc, string argv)
	{
		DerivedObject derived;
		print("derived.getValue() = " + derived.getValue());
		derived.setValue(2);
		print("derived.getValue() = " + derived.getValue());

		Retyped retyped;
		print("retyped.getValue() = " + retyped.getValue());
		retyped.setValue(2);
		print("retyped.getValue() = " + retyped.getValue());
	}
}

