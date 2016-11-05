#!/usr/local/bin/oscript

public namespace Language {
	public object TestObject {
		public int mValue;

		public void Constructor(int value) {
			mValue = value;
		}

		public int getValue() const {
			return mValue;
		}

		public void setValue(int value const) {
			mValue = value;
		}
	}
}

public void Main(int argc = 0, string argv = "") modify {
	assert( TestCase1() );
	//assert( TestCase2() );
	//assert( TestCase3() );
	assert( TestCase4() );
}

private bool TestCase1() const {
	print("TestCase1: parameter by value");

	Language.TestObject obj = new Language.TestObject(1);

	ParameterByValue(obj.mValue);

	return obj.mValue == 1;
}

private bool TestCase2() const {
	print("TestCase2: parameter as object by value");

	Language.TestObject obj = new Language.TestObject(1);

	ParameterByValue(obj);

	return obj.mValue == 1;
}

private bool TestCase3() const {
	print("TestCase3: parameter by reference");

	Language.TestObject obj = new Language.TestObject(1);

	ParameterByReference(obj.mValue);

	return obj.mValue == 2;
}

private bool TestCase4() modify {
	print("TestCase4: parameter as object by reference");

	Language.TestObject obj = new Language.TestObject(1);

	ParameterByReference(obj);

	return obj.mValue == 2;
}

private void ParameterByReference(int value ref) const {
	assert(value == 1);
	print("ParameterByReference(int): value = " + value);
	value = value + 1;
	print("ParameterByReference(int): value = " + value);
	assert(value == 2);
}

private void ParameterByReference(Language.TestObject value ref) modify {
	assert(value.mValue == 1);
	print("ParameterByReference(TestObject): mValue = " + value.mValue);
	value.mValue = value.mValue + 1;
	print("ParameterByReference(TestObject): mValue = " + value.mValue);
	assert(value.mValue == 2);
}

private void ParameterByValue(int value val) const {
	assert(value == 1);
	print("ParameterByValue(int): value = " + value);
	value = value + 1;
	print("ParameterByValue(int): value = " + value);
	assert(value == 2);
}

private void ParameterByValue(Language.TestObject value const) const {
	assert(value.mValue == 1);
	print("ParameterByValue(TestObject): mValue = " + value.mValue);
	value.mValue = value.mValue + 1;
	print("ParameterByValue(TestObject): mValue = " + value.mValue);
	assert(value.mValue == 2);
}

