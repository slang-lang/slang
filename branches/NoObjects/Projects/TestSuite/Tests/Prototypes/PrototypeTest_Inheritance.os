#!/usr/bin/oscript

public object Observer
{
	private String mTypeName;

	public void Observer() {
		mTypeName = "Observer";
	}

	public String getTypeName() const {
		return mTypeName;
	}
}

public prototype TestPrototype extends public Observer
{
	private UNKNOWN mValue;

	public void TestPrototype() {
		mTypeName = "TestPrototype";
		mValue = 0;
	}

	public void TestPrototype(UNKNOWN value) {
		mValue = value;
	}

	public UNKNOWN getValue() const {
		return mValue;
	}

	public void setValue(UNKOWN value) {
		mValue = value;
	}
}


public object Main
{
	public void Main(Number argc = 0, String argv = "")
	{
		test();
	}

	public void test()
	{
		TestPrototype of Number prototype = new TestPrototype of Number(100);

		print("Observer = " & prototype.getTypeName());

		// up- or downcast:
		//Observer o = prototype as Observer;
	}
}
