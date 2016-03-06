#!/usr/local/bin/oscript

private object BaseObject
{
	protected number mValue;

	public void BaseObject(number value)
	{
		print("BaseObject(" + value + ")");

		mValue = value;
	}

	public void ~BaseObject()
	{
		print("~BaseObject(" + mValue + ")");
	}
}

private object DerivedObject extends BaseObject
{
	public void DerivedObject()
	{
		print("DerivedObject()");

		base.BaseObject(5);
	}

	public void ~DerivedObject()
	{
		print("~DerivedObject(" + mValue + ")");
	}
}

public object Main
{
	public void Main(number argc = 0, string argv = "")
	{
		DerivedObject derived;
	}
}

