#!/usr/local/bin/oscript

import System.String;

public object Main
{
	public void Main(int argc, string args)
	{
		assert( TestCase1() );
		assert( TestCase2() );
		assert( TestCase3() );
		assert( TestCase4() );
	}

	private bool TestCase1() const
	{
		print("TestCase 1: String.StartsWith");

		String str = new String("This is a string");

		return str.StartsWith("This");
	}

	private bool TestCase2() const
	{
		print("TestCase 2: String.EndsWith");

		String str = new String("This is a string");

		return str.EndsWith("ring");
	}

	private bool TestCase3() const
	{
		print("TestCase 3: String.ToLowerCase");

		String str = new String("This is a string");

		return str.ToLowerCase() == "this is a string";
	}

	private bool TestCase4() const
	{
		print("TestCase 4: String.ToUpperCase");

		String str = new String("This is a string");

		return str.ToUpperCase() == "THIS IS A STRING";
	}
}

