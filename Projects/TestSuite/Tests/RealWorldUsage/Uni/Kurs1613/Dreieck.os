#!/usr/local/bin/slang

public void Main(int argc, string args) {
	writeln("Geben Sie eine natürlich Zahl ein: ");
	int n = int cin();

	for ( int i = 1; i <= n; i=i++ ) {
		for ( int j = 1; j <= i; j=j++ ) {
			write("X");
		}
		writeln();
	}
}

