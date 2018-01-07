#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	print("continue without loop");

	continue;

	print("after continue");

	for ( int i = 0; i < 3; i += 1 ) {
		print("for");
		continue;
		print("inc");
	}
}

