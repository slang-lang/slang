#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	int value ref = new int(173);

	print("value = " + value);

	assert( value == 173 );

	Method(value);

	print("value = " + value);

	assert( value == 174 );
}

private void Method(int value ref) {
	value++;
}

