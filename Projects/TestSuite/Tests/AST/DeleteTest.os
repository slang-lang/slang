#!/usr/local/bin/oscript

private object TestObject {
	public int mValue = 1;

	public void Destructor() {
		print("argh!");
	}
}

public void Main(int argc = 0, string args = "") {
	TestObject obj = new TestObject();
	assert( obj );

	delete obj;
	assert( !obj );
	print("after delete");
}

