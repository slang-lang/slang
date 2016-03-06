#!/usr/local/bin/oscript

private object TestObject
{
	public void TestObject()
	{
		print("TestObject()");

		print("throw in constructor");
		throw 17;
	}

	public void ~TestObject()
	{
		print("~TestObject()");
	}
}

public object Main
{
	public void Main(number argc, string argv)
	{
		try {
			TestObject obj;
		}
	}
}

