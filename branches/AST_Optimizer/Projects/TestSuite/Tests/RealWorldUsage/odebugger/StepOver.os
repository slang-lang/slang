#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	int i = 0;

	i += 1;
	print("i = " + i);
	i += 1;
	print("i = " + i);

	Method();

	i += 1;
	print("i = " + i);
	i += 1;
	print("i = " + i);
}

private void Method() {
	print("enter method");

	for ( int j = 0; j < 10; j += 1 ) {
		print("j = " + j);
	}

	print("exit method");
}

