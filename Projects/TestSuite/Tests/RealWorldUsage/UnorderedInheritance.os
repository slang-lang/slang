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
	public void Main(int argc, string argv)
	{
		DerivedObject derived;
	}
}

private object BaseObject
{
        public void BaseObject()
        {
                print("BaseObject");
        }
}

