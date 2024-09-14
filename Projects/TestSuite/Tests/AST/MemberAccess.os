#!/usr/local/bin/slang

private object BaseObject {
	public string mValue;
	private string mPrivateValue;

	public void Constructor(string value) {
		print("BaseObject.Constructor(" + value + ")");

		mPrivateValue = "this is private";
		mValue = value;
	}

	public string =operator(string none) const {
		return mValue;
	}

	public string toString() const {
		return mValue;
	}
}

private object TestObject {
	public BaseObject mBaseObject;

	public void Constructor(int value) {
		print("TestObject.Constructor(" + value + ")");

		mBaseObject = new BaseObject(string value);
	}

	public string =operator(string none) const {
		return string mBaseObject;
	}
}

public void Main(int argc, string args) {
	TestObject obj = new TestObject(1389);

	//print("obj = " + string obj);
	print(obj.mBaseObject.toString());
	print(obj.mBaseObject.mPrivateValue);
}

