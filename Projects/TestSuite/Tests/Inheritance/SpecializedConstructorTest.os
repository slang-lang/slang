#!/usr/local/bin/oscript

private object BaseObject
{
	protected number mValue;

	public void BaseObject(number value)
	{
		mValue = value;
		print("BaseObject(" + mValue + ")");
	}

	public void ~BaseObject()
	{
		print("~BaseObject(" + mValue + ")");
	}
}

private object DerivedObject extends BaseObject
{
	public void DerivedObject(number value)
	{
		print("DerivedObject(" + value + ")");

		base.BaseObject(value);
	}

	public void ~DerivedObject()
	{
		print("~DerivedObject(" + mValue + ")");
	}
}

public object Main
{
	public void Main(number argc, string argv)
	{
		DerivedObject derived = new DerivedObject(5);
		//DerivedObject derived;

		//delete derived;	// this should not be necessary because our garbage collection has to delete everything that's left over
	}
}

