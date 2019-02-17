#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	print("getenv Test");

	print("getenv(\"OBJECTIVESCRIPT_LIBRARY\") = " + getenv("OBJECTIVESCRIPT_LIBRARY"));
	print("getenv(\"bla\") = " + getenv("bla"));
	print("getenv(\"PATH\") = " + getenv("PATH"));
	print("getenv(\"GET\") = " + getenv("GET"));
}

