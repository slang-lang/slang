#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	int i = 0;
	for ( ; ; ) {
		if ( i > 4 )
			break;

		print("i = " + i);

		i++;
	}
}

