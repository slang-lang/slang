#!/usr/local/bin/oscript

private object BaseObject
{
	protected int mIntValue;

	public void BaseObject()
	{
		mIntValue = 0;
	}
}

private object Derived extends BaseObject
{
	protected string mStringValue;

	public void Derived()
	{
	}
}

public object Main
{
	public void Main(int argc, string args)
	{
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() /*const*/ modify
	{
		BaseObject baseObject;
		baseObject.mIntValue = 173;

		string jsonString = ToJsonString(Object baseObject);
		writeln("baseObject = " + jsonString);

		return true;
	}

	private bool TestCase2() /*const*/ modify
	{
		Derived derived;

		string jsonString = "{\"base\":{\"mIntValue\":\"42\"},\"mStringValue\":\"this is a string\"}";

		bool result = FromJsonString(Object derived, jsonString);
		result = result && jsonString == ToJsonString(Object derived);

		writeln("derived = " + ToJsonString(Object derived));

		return result;
	}
}

