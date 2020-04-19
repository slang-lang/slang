#!/usr/local/bin/slang

public void Main(int argc, string args) {
	print("break without loop");

	break;

	print("after break");

	while ( true ) {
		print("while");
		break;
		print("wend");
	}
}

