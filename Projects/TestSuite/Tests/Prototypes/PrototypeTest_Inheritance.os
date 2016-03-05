#!/usr/local/bin/oscript

public object Observer
{
	private string mTypeName;

	public void Observer() {
		mTypeName = "Observer";
	}

	public string getTypeName() const {
		return mTypeName;
	}
}

public prototype TestPrototype extends Observer
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
	public void Main(number argc = 0, string argv = "")
	{
		test();
	}

	public void test()
	{
		TestPrototype of number prototype = new TestPrototype of number(100);

		print("Observer = " & prototype.getTypeName());

		// up- or downcast:
		//Observer o = prototype as Observer;
	}
}
