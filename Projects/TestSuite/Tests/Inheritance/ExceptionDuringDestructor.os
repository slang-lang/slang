#!/usr/local/bin/oscript

private object TestObject
{
	public void TestObject()
	{
		print("TestObject()");
	}

	public void ~TestObject()
	{
		print("~TestObject()");

		print("throw in destructor");
		throw 42;
	}
}

public object Main
{
	public void Main(number argc = 0, string argv = "")
	{
		//try {
			TestObject obj;
		//}
	}
}

