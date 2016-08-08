#!/usr/local/bin/oscript

import System.String;

public object Main {
	public void Main(int argc, string args) {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() const {
		print("TestCase 1: toLower()");

		string str = "This is a string";
		print("toLower(str) = \"" + toLower(str) + "\"");

		return toLower(str) == "this is a string";
	}

	private bool TestCase2() const {
		print("TestCase 2: String.ToLowerCase()");

		String str = new String("This is a string");
		print("str.ToLowerCase() = \"" + str.ToLowerCase() + "\"");

		return str.ToLowerCase() == "this is a string";
	}
}

