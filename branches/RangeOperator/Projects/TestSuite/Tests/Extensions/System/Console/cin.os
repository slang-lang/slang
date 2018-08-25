#!/usr/local/bin/oscript

public int Main(int argc, string args) {
	writeln("cin Test");

	write("Prompt> ");

	string text = cin();

	writeln("text = \"" + text + "\"");

	return 0;
}

