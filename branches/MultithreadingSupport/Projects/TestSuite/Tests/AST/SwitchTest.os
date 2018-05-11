#!/usr/local/bin/oscript

public void Main(int argc = 1, string args = "") {
	int value = 3;

	switch ( value ) {
		case 0: { print("case 0"); assert( false ); break; }
		case 3: { print("case 3"); break; }
		default: { print("default"); assert( false ); break; }
	}

	print("after switch (1)");

	switch ( value ) {
		case 3: { print("case 3"); value += 1; continue; }
		case 4: { print("case 4"); value += 1; continue; }
		case 5: { print("case 5"); value -= 1; break; }
		default: { print("default"); break; }
	}

	print("after switch (2)");

	switch ( 0 ) {
		case 1: { print("case 1"); assert( false ); break; }
		default: { print("default"); break; }
	}

	print("after switch (3)");
}

