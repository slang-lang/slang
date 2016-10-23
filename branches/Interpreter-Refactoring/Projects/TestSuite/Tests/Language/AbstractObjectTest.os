#!/usr/local/bin/oscript

public abstract object AbstractObject {
	public bool isAbstract() const abstract;
}

public object ImplementedObject extends AbstractObject {
	public bool isAbstract() const {
		return false;
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase 1: implemented object instantiation");

	AbstractObject obj = new ImplementedObject();

	print("obj.isAbstract() = " + obj.isAbstract());

	assert( obj is Object );
	assert( obj is AbstractObject );
	assert( obj is ImplementedObject );
	assert( !obj.isAbstract() );

	return true;
}

private bool TestCase2() const {
	print("TestCase 2: abstract object instantiation");

	AbstractObject obj = new AbstractObject();

	print("obj.isAbstract() = " + obj.isAbstract());
}

