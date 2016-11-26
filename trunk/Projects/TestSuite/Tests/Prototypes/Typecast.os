#!/usr/local/bin/oscript

private object Prototype<T> {
	public T mValue;
}

private object TestObject extends Prototype<int> {
}

public void Main(int argc = 0, string args = "") {
	TestObject obj = new TestObject();

	//assert( obj is Prototype<int> );

	Prototype<int> p = Prototype<int> obj;
	assert( p == obj );
}

