#!/usr/local/bin/oscript

public object BaseObject {
	protected int mIntValue;
}

public object DerivedObject extends BaseObject {
	protected string mStringValue;
}

public void Main(int argc = 0, string args = "") {
	BaseObject baseObject = new BaseObject();
	DerivedObject derivedObj = new DerivedObject();

	print("baseObject is BaseObject");
	assert(baseObject is BaseObject);

	print("derivedObj is DerivedObject");
	assert(derivedObj is DerivedObject);

	print("derivedObj is BaseObject");
	assert(derivedObj is BaseObject);

	print("derivedObj is baseObject");
	assert(derivedObj is baseObject);

	if ( derivedObj is BaseObject ) {
		print("positive is in if");
	}
	if ( !(derivedObj is BaseObject) ) {
		print("negative is in if");
	}

	bool result = derivedObj is BaseObject;
	assert(result);
}

