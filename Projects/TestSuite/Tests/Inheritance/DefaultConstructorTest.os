#!/usr/local/bin/oscript

//import DerivedObject;

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
	}

	public void ~DerivedObject()
	{
		print("~DerivedObject()");
	}
}

public object Main
{
	public void Main(number argc = 0, string argv = "")
	{
		DerivedObject derived;
	}
}
