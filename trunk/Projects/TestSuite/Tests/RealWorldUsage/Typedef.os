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

private object RetypedObject extends TestObject
{
	public void setValue(number value) modify
	{
		mValue = value * value;
	}
}

private object Retyped replicates TestObject;

private object Main
{
	private object InnerObject { }

	public void Main(number argc, string argv)
	{
		InnerObject inner;

		RetypedObject obj1;
		print(obj1.getValue());
		obj1.setValue(2);
		print(obj1.getValue());

		Retyped obj2;
		print(obj2.getValue());
	}
}

