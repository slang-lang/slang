#!/usr/local/bin/oscript

public object BaseObject {
	protected int mIntValue;

	private void Constructor() { }
}

public object DerivedObject extends BaseObject {
	protected string mStringValue;

	private void Constructor() { }
}

public void Main(int argc = 0, string args = "") {
	BaseObject baseObject = new BaseObject();
	DerivedObject derived = new DerivedObject();

	assert(baseObject is BaseObject);
	print("baseObject is BaseObject");

	assert(derived is DerivedObject);
	print("derived is DerivedObject");

	assert(derived is BaseObject);
	print("derived is BaseObject");

	print("derived is baseObject");
	assert(derived is baseObject);

	if ( derived is BaseObject ) {
		print("positive is in if");
	}
	if ( !(derived is BaseObject) ) {
		print("negative is in if");
	}

	bool result = derived is BaseObject;
	assert(result);
}

