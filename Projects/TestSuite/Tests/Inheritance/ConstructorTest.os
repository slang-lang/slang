#!/usr/local/bin/oscript

private object BaseObject
{
	public void BaseObject()
	{
		print("BaseObject()");
	}

	public void ~BaseObject()
	{
		print("~BaseObject()");
	}
}

private object DerivedObject extends BaseObject
{
	public void DerivedObject()
	{
		print("DerivedObject()");

		//base.BaseObject();
	}

	public void ~DerivedObject()
	{
		print("~DerivedObject()");
	}
}

public object Main
{
	public void Main(number argc, string argv)
	{
		DerivedObject derived;
	}
}

