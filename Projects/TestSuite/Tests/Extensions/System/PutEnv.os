#!/usr/bin/env slang

public void Main(int argc, string args) {
	print("putenv Test");

	putenv("foo=bar");
	print("getenv(\"foo\") = " + getenv("foo"));
}

