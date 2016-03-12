
import BaseObject;

private object DerivedObject extends BaseObject
{
	public void DerivedObject()
	{
		print("DerivedObject::DerivedObject()");
	}

	public void ~DerivedObject()
	{
		print("DerivedObject::~DerivedObject()");
	}
	
	public string ToString() const 
	{
		return "DerivedObject { mValue = " + mValue + "}";
	}
}
