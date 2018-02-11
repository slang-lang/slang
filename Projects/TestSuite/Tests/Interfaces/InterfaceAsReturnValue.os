#!/usr/local/bin/oscript

private stable interface IInterface {
	public bool IsInterface() const;
}

private object TestObject implements IInterface {
	public bool IsInterface() const {
		return true;
	}
}

private IInterface createTestObject() {
	TestObject obj = new TestObject();
	return IInterface obj;
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1: interface as return value");

	IInterface obj = createTestObject();
	assert( obj );
	assert( obj is Object );
	assert( obj is IInterface );
	assert( obj is TestObject );

	assert( obj.IsInterface() );

	return true;
}

