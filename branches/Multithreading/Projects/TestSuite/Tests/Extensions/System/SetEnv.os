#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	print("setenv Test");

	setenv("foo", "bar", 1);
	print("getenv(\"foo\") = " + getenv("foo"));
}

