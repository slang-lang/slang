#!/usr/local/bin/oscript

private object BaseObject {
	public int mIntValue;

	public void Constructor() {
		mIntValue = 0;
	}
}

private object Derived extends BaseObject {
	public string mStringValue;
}

private object Replica replicates Derived;

public void Main(int argc, string args) {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

private bool TestCase1() const {
	try {
		BaseObject baseObject = new BaseObject();
		baseObject.mIntValue = 173;

		string jsonString = ToJsonString(baseObject);
		writeln("baseObject = " + jsonString);

		return true;
	}

	return false;
}

private bool TestCase2() const {
	try {
		Derived derived = new Derived();

		string jsonString = "{\"base\":{\"mIntValue\":\"42\"},\"mStringValue\":\"this is a string\"}";

		bool result = FromJsonString(derived, jsonString);
		result = result && jsonString == ToJsonString(derived);

		writeln("derived = " + ToJsonString(derived));
		writeln(jsonString + " == " + ToJsonString(derived));

		return result;
	}

	return false;
}

private bool TestCase3() const {
	try {
		Replica replica;

		string jsonString = "{\"base\":{\"mIntValue\":\"42\"},\"mStringValue\":\"this is a string\"}";

		bool result = FromJsonString(replica, jsonString);
		result = result && jsonString == ToJsonString(replica);

		writeln("replica = " + ToJsonString(replica));

		return result;
	}

	return false;
}

