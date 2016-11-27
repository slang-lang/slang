#!/usr/local/bin/oscript

public interface IInterface {
	public bool isAbstract() const;
}

public object AbstractObject implements IInterface {
}

public object ImplementedObject implements IInterface {
	public bool isAbstract() const {
		return false;
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );	// this test currently fails
}

private bool TestCase1() {
	print("TestCase 1: implemented object");

	ImplementedObject obj = new ImplementedObject();

	assert( obj );
	assert( obj is ImplementedObject );
	assert( obj is IInterface );
	assert( obj is Object );

	return !obj.isAbstract();
}

private bool TestCase2() {
	print("TestCase 2: abstract object");

	AbstractObject obj = new AbstractObject();
	//assert( obj.isAbstract() );

	return false;
}

