#!/usr/local/bin/oscript

import System.Math;

public object Main
{
	public void Main(int argc, string argv)
	{
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() const
	{
		print("TestCase 1: abs");

		float floatValue = -17.3f;
		print("abs(float: " + floatValue + ") = " + abs(floatValue));
		floatValue = floatValue * -1;
		print("abs(float: " + floatValue + ") = " + abs(floatValue));

		int intValue = -17;
		print("abs(int: " + intValue + ") = " + abs(intValue));
		intValue = intValue * -1;
		print("abs(int: " + intValue + ") = " + abs(intValue));

		number numberValue = -173.1389;
		print("abs(number: " + numberValue + ") = " + abs(numberValue));
		numberValue = numberValue * -1;
		print("abs(number: " + numberValue + ") = " + abs(numberValue));

		return true;
	}

	private bool TestCase2() const
	{
		print("TestCase 2: power");

		float floatValue = -17.3f;
		print("power(float: " + floatValue + ") = " + power(floatValue));

		int intValue = -17;
		print("power(int: " + intValue + ") = " + power(intValue));

		number numberValue = 173.1389;
		print("power(number: " + numberValue + ") = " + power(numberValue));

		return true;
	}
}

