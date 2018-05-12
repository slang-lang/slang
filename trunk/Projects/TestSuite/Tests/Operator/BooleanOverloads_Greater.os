#!/usr/local/bin/oscript

private object UserObject
{
	private int mValue;

	public void Constructor(int value const)
	{
		mValue = value;
	}

	public int GetValue() const
	{
		return mValue;
	}
	
	/////////////////////////////////////////////////////////////////////
	
	public bool operator>(int other const) const
	{
		print("operator>(int)");
		return mValue > other;
	}

	public bool operator>(UserObject other const) const
	{
		print("operator>(UserObject)");
		return mValue > other.GetValue();
	}
}

public void Main(int argc = 0, string argv = "")
{
	assert(TestCase1());
	assert(TestCase2());
}

private bool TestCase1() const
{
	print("TestCase1: greater operator with atomic type");

	UserObject obj1 = new UserObject(2);

	//assert(obj1 > 1);
	if ( obj1 > 1 ) {
		print("obj1 > 1");
		return true;
	}

	return false;
}

private bool TestCase2() const
{
	print("TestCase2: greater operator with object");

	UserObject obj1 = new UserObject(1);
	UserObject obj2 = new UserObject(2);

	//assert(obj2 > obj1);
	if ( obj2 > obj1 ) {
		print("obj2 > obj1");
		return true;
	}

	return false;
}

