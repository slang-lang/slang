#!/usr/local/bin/oscript

import System.Math;

public object Main {
	public void Main(int argc, string argv) {
		print("PI = " + Math.PI);

		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() const {
		print("TestCase 1: abs");

		double doubleValue = -17.31d;
		print("abs(double: " + doubleValue + ") = " + Math.abs(doubleValue));
		doubleValue = doubleValue * -1;
		print("abs(double: " + doubleValue + ") = " + Math.abs(doubleValue));

		float floatValue = -17.31f;
		print("abs(float: " + floatValue + ") = " + Math.abs(floatValue));
		floatValue = floatValue * -1;
		print("abs(float: " + floatValue + ") = " + Math.abs(floatValue));

		int intValue = -17;
		print("abs(int: " + intValue + ") = " + Math.abs(intValue));
		intValue = intValue * -1;
		print("abs(int: " + intValue + ") = " + Math.abs(intValue));

		number numberValue = -173.1389;
		print("abs(number: " + numberValue + ") = " + Math.abs(double numberValue));
		numberValue = numberValue * -1;
		print("abs(number: " + numberValue + ") = " + Math.abs(double numberValue));

		return true;
	}

	private bool TestCase2() const {
		print("TestCase 2: power");

		float floatValue = -17.3f;
		print("power(float: " + floatValue + ") = " + Math.power(floatValue));

		int intValue = -17;
		print("power(int: " + intValue + ") = " + Math.power(intValue));

		number numberValue = -173.1389;
		print("power(number: " + numberValue + ") = " + Math.power(double numberValue));

		return true;
	}
}

