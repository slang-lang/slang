#!/usr/local/bin/slang

public int Main(int argc, string args) {
	print("getchar Test");

	string c;
	string text;

//	setKeyboardBlocking(false);

	while ( c != "q" ) {
		c = getchar();

		if ( c ) {
			text = text + c;
		}
	}

	print("text = " + text);

//	setKeyboardBlocking(true);

	return 0;
}

