#!/usr/local/bin/oscript

private object DerivedObject extends BaseObject
{
	public void DerivedObject()
	{
		print("DerivedObject");
	}
}

public object Main
{
	public void Main(int argc = 0, string args = "")
	{
		DerivedObject derived = new DerivedObject();
	}
}

private object BaseObject
{
        public void BaseObject()
        {
                print("BaseObject");
        }
}

