#!/usr/local/bin/oscript

private object BaseObject {
	public int mIntValue;

	public void Constructor() {
		mIntValue = 0;
	}
}

private object DerivedObject extends BaseObject {
	public string mStringValue;

	public void Constructor() {
		mStringValue = "";
	}
}

public void Main(int argc, string argv) {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	BaseObject baseObject = new BaseObject();
	baseObject.mIntValue = 173;

	string jsonString = ToJsonString(baseObject);
	writeln("jsonString = " + jsonString);

	bool result = FromJsonString(baseObject, jsonString);
	return result && baseObject.mIntValue == 173;
}

private bool TestCase2() const {
	DerivedObject derived = new DerivedObject();
	derived.mIntValue = 42;
	derived.mStringValue = "this is a string";

	string jsonString = ToJsonString(derived);
	writeln("jsonString = " + jsonString);

	bool result = FromJsonString( derived, jsonString);
	return result && derived.mIntValue == 42;
}

