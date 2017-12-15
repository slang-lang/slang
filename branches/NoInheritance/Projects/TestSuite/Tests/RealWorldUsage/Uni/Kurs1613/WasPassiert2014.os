#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	int a = 0;
	int b = 0;
	int c = 1;

	write("a = ");
	a = int cin();
	writeln("b = " + b);
	writeln("c = " + c);

	while ( a > 0 ) {
		b = b + c * (a % 2);
		a = a / 2;
		c = c * 10;
	}

	writeln("=> b = " + b);
}

