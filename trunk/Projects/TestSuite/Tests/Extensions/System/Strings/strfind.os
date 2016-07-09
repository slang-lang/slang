#!/usr/local/bin/oscript

import System.String;

public object Main {
	public void Main(int argc, string args) {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() const {
		print("TestCase 1: strfind()");

		string str = "This is a string";
		int position = strfind(str, "is a");
		print("strfind(str, \"is a\") = " + position);

		return position == 5;
	}

	private bool TestCase2() const {
		print("TestCase 2: String.Find()");

		String str = new String("This is a string");
		print("str.Find(\"is a\") = " + str.Find("is a"));

		return str.Find("is a") == 5;
	}
}

