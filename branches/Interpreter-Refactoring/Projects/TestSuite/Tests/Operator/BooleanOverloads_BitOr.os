#!/usr/local/bin/oscript

private object UserObject
{
	private bool mValue;

	public void UserObject(bool value const)
	{
		mValue = value;
	}

	public bool getValue() const
	{
		return mValue;
	}

	public void setValue(bool value const)
	{
		mValue = value;
	}

	/////////////////////////////////////////////////////////////////////

	public void operator|(bool other const) modify
	{
		mValue = mValue | other;
	}

	public void operator|(UserObject other const ref) modify
	{
		mValue = mValue | other.getValue();
	}

	public bool operator==(bool other const) const
	{
		return mValue == other;
	}

	public bool operator==(UserObject other const ref) const
	{
		return mValue == other.getValue();
	}
}

public void Main(int argc = 0, string argv = "")
{
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const
{
	print("TestCase1: bitor operator with atomic type");

	UserObject obj1 = new UserObject(true);

	obj1 = obj1 | true;
	//assert( obj1 == true );
	if ( obj1 == true ) {
		print("obj1 == true");
		return true;
	}

	return false;
}

private bool TestCase2() const
{
	print("TestCase2: bitor operator with object");

	UserObject obj1 = new UserObject(true);
	UserObject obj2 = new UserObject(false);

	obj1 = obj1 | obj2;
	//assert( obj1 == true );
	if ( obj1 == true ) {
		print("obj1 == true");
		return true;
	}

	return false;
}

