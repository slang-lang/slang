#!/usr/local/bin/oscript

private object BaseObject {
	protected int mIntValue;

	public void BaseObject() {
		mIntValue = 0;
	}
}

private object Derived extends BaseObject {
	protected string mStringValue;
}

private object Replica replicates Derived;

public object Main {
	public void Main(int argc, string args) {
		assert( TestCase1() );
		assert( TestCase2() );
		assert( TestCase3() );
	}

	private bool TestCase1() /*const*/ modify {
		try {
			BaseObject baseObject = new BaseObject();
			baseObject.mIntValue = 173;

			string jsonString = ToJsonString(Object baseObject);
			writeln("baseObject = " + jsonString);

			return true;
		}
		catch ( string e ) {
			print(e);
		}

		return false;
	}

	private bool TestCase2() /*const*/ modify {
		try {
			Derived derived = new Derived();

			string jsonString = "{\"base\":{\"mIntValue\":\"42\"},\"mStringValue\":\"this is a string\"}";

			bool result = FromJsonString(Object derived, jsonString);
			result = result && jsonString == ToJsonString(Object derived);

			writeln("derived = " + ToJsonString(Object derived));

			return result;
		}
		catch ( string e ) {
			print(e);
		}

		return false;
	}

	private bool TestCase3() /*const*/ modify {
		try {
			Replica replica;

			string jsonString = "{\"base\":{\"mIntValue\":\"42\"},\"mStringValue\":\"this is a string\"}";

			bool result = FromJsonString(Object replica, jsonString);
			result = result && jsonString == ToJsonString(Object replica);

			writeln("replica = " + ToJsonString(Object replica));

			return result;
		}
		catch ( string e ) {
			print(e);
		}

		return false;
	}
}

