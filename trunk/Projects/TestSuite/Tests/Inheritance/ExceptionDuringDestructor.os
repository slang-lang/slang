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
		throw;
	}
}

public object Main
{
	public void Main(number argc, string argv)
	{
		//try {
			TestObject obj;
		//}
	}
}

