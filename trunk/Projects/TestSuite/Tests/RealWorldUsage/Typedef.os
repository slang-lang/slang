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
		DerivedObject obj1;
		print("obj1.getValue() = " + obj1.getValue());
		obj1.setValue(2);
		print("obj1.getValue() = " + obj1.getValue());

		Retyped obj2;
		print("obj2.getValue() = " + obj2.getValue());
		obj2.setValue(2);
		print("obj2.getValue() = " + obj2.getValue());
	}
}

