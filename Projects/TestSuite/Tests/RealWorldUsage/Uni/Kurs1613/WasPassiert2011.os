#!/usr/local/bin/slang

public void Main(int argc, string args) {
	int a = 0;
	int b = 0;

	write("Geben Sie zwei natürliche Zahlen ein: ");
	a = int cin();
	b = int cin();

	if ( a > b ) {
		b = a + b;
		a = b - a;
		b = b - a;
	}

	while ( a < b ) {
		a = a + 1;
		b = b - 1;
	}

	if ( a == b ) {
		writeln("Ergebnis: " + b);
	}
	else {
		writeln("Ergebnis: " + b + ".5");
	}
}

