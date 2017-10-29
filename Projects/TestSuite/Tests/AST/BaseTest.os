#!/usr/local/bin/oscript

private object BaseObject {
	protected int mValue;

	public void Constructor(int value) {
		print(typeid(this) + ".Constructor(" + value + ")");

		mValue = value;
	}
}

private object DerivedObject extends BaseObject {
	public void Constructor(int value) {
		print(typeid(this) + ".Constructor(" + value + ")");

		base.Constructor(value + 1);
	}

	public string =operator(string none) const {
		return string mValue;
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() {
	print("TestCase 1");

	DerivedObject derivedObj = new DerivedObject(173);

	print("derivedObj = " + string derivedObj);

	return true;
}

private bool TestCase2() {
	print("TestCase 2");

	BaseObject baseObj = new BaseObject(1);
	BaseObject derivedObj = BaseObject new DerivedObject(2);

	assert( baseObj is Object );
	assert( baseObj is BaseObject );
	assert( derivedObj is Object );
	assert( derivedObj is BaseObject );
	assert( derivedObj is DerivedObject );

	return true;
}

