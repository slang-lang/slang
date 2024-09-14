#!/usr/local/bin/slang

public void Main(int argc, string args) {
	print("getenv Test");

	print("getenv(\"SLANG_LIBRARY\") = " + getenv("SLANG_LIBRARY"));
	print("getenv(\"bla\") = " + getenv("bla"));
	print("getenv(\"PATH\") = " + getenv("PATH"));
	print("getenv(\"GET\") = " + getenv("GET"));
}

