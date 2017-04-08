#!/usr/local/bin/oscript

private object TestObject {
	public int mValue = 173;
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() {
	int i = 1;
	print("i = " + i);

	i++;
	print("i = " + i);

	i--;
	print("i = " + i);


	bool value = true;

	assert( value );
	assert( value! );

	print("value = " + value);
	print("value = " + value!);

	value = false;

	assert( true! );
	assert( !false! );
	assert( value! );
}

private bool TestCase2() {
	TestObject obj;

	print(obj!.mValue);
}

