#!/usr/local/bin/oscript

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

