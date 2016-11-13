#!/usr/local/bin/oscript

private object BaseObject {
	protected int mIntValue;

	public void BaseObject() {
		mIntValue = 0;
	}
}

private object DerivedObject extends BaseObject {
	protected string mStringValue;

	public void DerivedObject() {
		mStringValue = "";
	}
}

public void Main(int argc, string argv) modify {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() /*const*/ modify {
	BaseObject baseObject = new BaseObject();
	baseObject.mIntValue = 173;

	string jsonString = ToJsonString(Object baseObject);
	writeln("jsonString = " + jsonString);

	bool result = FromJsonString(Object baseObject, jsonString);
	return result && baseObject.mIntValue == 173;
}

private bool TestCase2() /*const*/ modify {
	DerivedObject derived = new DerivedObject();
	derived.mIntValue = 42;
	derived.mStringValue = "this is a string";

	string jsonString = ToJsonString(Object derived);
	writeln("jsonString = " + jsonString);

	bool result = FromJsonString(Object derived, jsonString);
	return result && derived.mIntValue == 42;
}

