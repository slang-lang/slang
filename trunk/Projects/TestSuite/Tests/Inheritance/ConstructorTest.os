#!/usr/local/bin/oscript

private object BaseObject
{
	public void BaseObject()
	{
		//print("BaseObject::BaseObject()");
	}

	public void ~BaseObject()
	{
		print("BaseObject::~BaseObject()");
	}
}

private object DerivedObject extends BaseObject
{
	public void DerivedObject()
	{
		base.BaseObject();

		//print("DerivedObject::DerivedObject()");
	}

	public void ~DerivedObject()
	{
		print("DerivedObject::~DerivedObject");

		delete base;
	}
}

public object Main
{
	public void Main(number argc, string argv)
	{
		DerivedObject derived = new DerivedObject();
		//DerivedObject derived;

		//delete derived;	// this should not be necessary because our garbage collection has to delete everything that's left over
	}
}

