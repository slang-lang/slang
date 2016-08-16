#!/usr/local/bin/oscript

public object BaseObject {
	protected int mIntValue;
}

public object DerivedObject extends BaseObject {
	protected string mStringValue;
}

public object Main {
	public void Main(int argc = 0, string args = "") {
		DerivedObject derived = new DerivedObject();

		assert(derived is DerivedObject);
		print("derived is DerivedObject");

		assert(derived is BaseObject);
		print("derived is BaseObject");

		if ( derived is BaseObject ) {
			print("positive is in if");
		}
		if ( !(derived is BaseObject) ) {
			print("negative is in if");
		}

		bool result = derived is BaseObject;
		assert(result);
	}
}

