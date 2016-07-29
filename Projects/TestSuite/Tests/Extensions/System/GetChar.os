#!/usr/local/bin/oscript

public int Main(int argc, string args) {
	print("getchar Test");

	string c;
	string text;
	
	while ( c != "q" ) {
		c = getchar();

//		if ( c ) {
		text = text + c;
//		}
	}

	print("text = " + text);

	return 0;
}

