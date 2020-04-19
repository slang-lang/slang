#!/usr/local/bin/slang

private object TestObject {
	private int mValue;

	public void Constructor(int value) {
		print("Constructor(" + value + ")");

		mValue = value;
	}

	public void Destructor() {
		print("Destructor(" + mValue + ")");
	}

	public int getValue() const {
		return mValue;
	}
	public void setValue(int value) modify {
		mValue = value;
	}

	public string =operator(string none) const {
		return string mValue;
	}
}

public void Main(int argc = 1, string args = "") {
	TestObject obj1;
	TestObject obj2;

	{
		obj1 = new TestObject(1);
		print("obj1 = " + string obj1);
		assert( obj1.getValue() == 1 );

		obj2 = obj1;
		print("obj2 = " + string obj2);
		assert( obj2.getValue() == 1 );

		obj1.setValue(173);
		print("obj1 == obj2 == " + string obj1);
		assert( obj2.getValue() == 173 );

		obj1 = new TestObject(2);
		print("obj1 = " + string obj1.getValue());
		print("obj2 = " + string obj2);
		assert( obj1.getValue() == 2 );
	}

	print("obj1 = " + string obj1);
	print("obj2 = " + string obj2);

	delete obj1;
	delete obj1;
	delete obj1;

	//print("obj1 = " + string obj1);
	print("obj2 = " + string obj2);
}

