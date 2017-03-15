#!/usr/local/bin/oscript

private object Prototype<T> {
	public T mValue;
}

private object TestObject extends Prototype<int> {
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() {
	print("TestCase 1: is operator");

	TestObject obj = new TestObject();

	assert( obj is Prototype<int> );
	return obj is Prototype<int>;
}

private bool TestCase2() {
	print("TestCase 2: typecast");

	TestObject obj = new TestObject();

	Prototype<int> p = Prototype<int> obj;
	assert( p == obj );

	return p == obj;
}

