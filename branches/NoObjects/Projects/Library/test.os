
public object BaseObject
{
	protected String mName;
	private String mType;
	public Number mValue;

	public BaseObject BaseObject(String name const)
	{
		mName = name;
		mType = "BaseObject";
		mValue = 1;
	}

	public String getName() const 
	{
		return mName;
	}

	public String getType() const
	{
		return mType;
	}

	public Number getValue() const
	{
		return mValue;
	}
}

public object DerivedObject extends public BaseObject
{
	private String mType;

	public DerivedObject DerivedObject(String name const, String type const)
//	: BaseObject(name)
	{
		mName = name;
		mType = "DerivedObject";
		mValue = 2;
	}

	public String getType() const
	{
		return mType;
	}
}

private object Main
{
	private BaseObject base;
	private DerivedObject derived;

	public void Main()
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
