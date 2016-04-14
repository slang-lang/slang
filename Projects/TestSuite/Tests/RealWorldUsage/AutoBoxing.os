#!/usr/local/bin/oscript

import System.Types;

public object Main
{
	public void Main(int argc, string args)
	{
		assert( TestCase1() );
		assert( TestCase2() );
		assert( TestCase3() );
	}

	private void Reference(int value ref) {
		value = value + 2;
	}

	private void Reference(Integer value ref) {
		value = value + 2;
	}

	private bool TestCase1() const {
		print("TestCase 1");

		int value = 173;

		print("value = " + value);
		Reference(value);
		print("value = " + value);

		return true;
	}

	private bool TestCase2() const {
		print("TestCase 2");

		Integer value = new Integer(173);
		value = 17;

		print("value = " + value.ToString());
		Reference(value);
		print("value = " + value.ToString());

		value = value * 2;
		print("value = " + value.ToString());

		value = value - 2;
		print("value = " + value.ToString());

		value = value / 2;
		print("value = " + value.ToString());

		return true;
	}

	private bool TestCase3() const {
		Boolean value = new Boolean(true);

		print("value = " + value.ToString());
		value = !value;
		print("value = " + value.ToString());

		return true;
	}
}

