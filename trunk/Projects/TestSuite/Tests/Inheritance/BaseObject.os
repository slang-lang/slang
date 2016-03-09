
public object BaseObject
{
	private number mValue;

	public void BaseObject()
	{
		print("BaseObject::BaseObject()");
	}

	public void ~BaseObject()
	{
		print("BaseObject::~BaseObject()");
	}

	public number getValue() const
	{
		return mValue;
	}

	public void setValue(number value) modify
	{
		mValue = value;
	}
	
	public string ToString() const
	{
		return "BaseObject { mValue = " + mValue + " }";
	}
}
