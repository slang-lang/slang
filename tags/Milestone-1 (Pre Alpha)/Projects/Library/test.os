#!/usr/bin/oscript

public object BaseObject
{
	protected string mName;
	private string mType;
	public number mValue;

	public void BaseObject(string name const)
	{
		mName = name;
		mType = "BaseObject";
		mValue = 1;
	}

	public string getName() const
	{
		return mName;
	}

	public string getType() const
	{
		return mType;
	}

	public number getValue() const
	{
		return mValue;
	}
}

public object DerivedObject extends public BaseObject
{
	private string mType;

	public void DerivedObject(string name const, string type const)
//	: BaseObject(name)
	{
		mName = name;
		mType = "DerivedObject";
		mValue = 2;
	}

	public string getType() const
	{
		return mType;
	}
}

private object Main
{
	private BaseObject base;
	private DerivedObject derived;

	public void Main(number argc, string argv)
	{
		base = new BaseObject("base");
		print("name = " & base.getName());
		print("type = " & base.getType());
		print("value = " & base.getValue());

		derived = new DerivedObject("derived", "DerivedObject");
		print("name = " & derived.getName());
		print("type = " & derived.getType());
		print("value = " & derived.getValue());
	}

	public void ~Main()
	{
	}

	public void test1() const
	{
		print("name = " & base.mValue);
		print("type = " & base.mValue);
		print("value = " & base.mValue);
	}
}
