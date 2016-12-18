#!/usr/local/bin/oscript

public void Main(int argc = 1, string args = "") {
	int value = 5;

	switch ( value ) {
		case 0: print("case 0"); break;
		case 1: print("case 1"); break;
		case 5: print("case 5"); break;
		default: print("default"); break;
	}

	print("after switch");
}

