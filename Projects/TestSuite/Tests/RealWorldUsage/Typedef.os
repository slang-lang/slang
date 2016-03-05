#!/usr/local/bin/oscript

private object TestObject
{
	private number mValue;

	public number getValue() const
	{
		return mValue;
	}

	public void setValue(number value) modify
	{
		mValue = value;
	}
}

private object DerivedObject extends TestObject
{
	public void setValue(number value) modify
	{
		mValue = value * value;
	}
}

private object Retyped replicates TestObject;

//private prototype Proto<

private object Main
{
	public void Main(number argc, string argv)
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

