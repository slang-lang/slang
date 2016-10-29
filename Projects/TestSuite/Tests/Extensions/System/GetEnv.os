#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	writeln("getenv Test");

	writeln("getenv(\"OBJECTIVESCRIPT_LIBRARY\") = " + getenv("OBJECTIVESCRIPT_LIBRARY"));
	writeln("getenv(\"bla) = " + getenv("bla"));
	writeln("getenv(\"PATH\") = " + getenv("PATH"));
	writeln("getenv(\"GET\") = " + getenv("GET"));
}

