#!/usr/local/bin/oscript

public void Main(int argc = 1, string args = "") {
	int value = 3;

	switch ( value ) {
		case 0: { print("case 0"); break; }
		case 3: { print("case 5"); break; }
		default: { print("default"); break; }
	}

	print("after switch (1)");

	switch ( value ) {
		case 3: { print("case 3"); value += 1; }
		case 4: { print("case 4"); value += 1; }
		case 5: { print("case 5"); value -= 1; }
		default: { print("default"); }
	}

	print("after switch (2)");
}

