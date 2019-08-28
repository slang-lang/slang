#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	print("putenv Test");

	putenv("foo=bar");
	print("getenv(\"foo\") = " + getenv("foo"));
}

