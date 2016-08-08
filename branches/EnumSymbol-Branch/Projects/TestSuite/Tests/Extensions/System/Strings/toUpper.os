#!/usr/local/bin/oscript

import System.String;

public object Main {
	public void Main(int argc, string args) {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() const {
		print("TestCase 1: toUpper()");

		string str = "This is a string";
		print("toUpper(str) = \"" + toUpper(str) + "\"");

		return toUpper(str) == "THIS IS A STRING";
	}

	private bool TestCase2() const {
		print("TestCase 2: String.ToUpperCase()");

		String str = new String("This is a string");
		print("str.ToUpperCase() = \"" + str.ToUpperCase() + "\"");

		return str.ToUpperCase() == "THIS IS A STRING";
	}
}

