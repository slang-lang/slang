#!/usr/local/bin/oscript

public void Main(int argc, string args) {
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

