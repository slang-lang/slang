#!/usr/local/bin/oscript

import System.String;

public object Main {

	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
		assert( TestCase2() );
		assert( TestCase3() );
		assert( TestCase4() );
		assert( TestCase5() );
		assert( TestCase6() );
	}

	private bool TestCase1() const {
		print("TestCase 1: String.StartsWith");

		String str = new String("This is a string");
		print("str.StartsWith(\"This\") = " + str.StartsWith("This"));

		return str.StartsWith("This");
	}

	private bool TestCase2() const {
		print("TestCase 2: String.EndsWith");

		String str = new String("This is a string");
		print("str.EndsWith(\"ring\") = " + str.EndsWith("ring"));

		return str.EndsWith("ring");
	}

	private bool TestCase3() const {
		print("TestCase 3: String.ToLowerCase");

		String str = new String("This is a string");
		print("str.ToLowerCase() = " + (str.ToLowerCase() == "this is a string"));

		return str.ToLowerCase() == "this is a string";
	}

	private bool TestCase4() const {
		print("TestCase 4: String.ToUpperCase");

		String str = new String("This is a string");
		print("str.ToUpperCase() = " + (str.ToUpperCase() == "THIS IS A STRING"));

		return str.ToUpperCase() == "THIS IS A STRING";
	}

	private bool TestCase5() modify {
		print("TestCase 5: String.Replace");

		String str = new String("This is a string");
		str.Replace("is", "was");

		print(str.Value());

		return str == "Thwas is a string";
	}

	private bool TestCase6() modify {
		print("TestCase 6: String.ReplaceAll");

		String str = new String("This is a string");
		str.ReplaceAll("is", "was");

		print(str.Value());

		return str.Value() == "Thwas was a string";
	}

}

