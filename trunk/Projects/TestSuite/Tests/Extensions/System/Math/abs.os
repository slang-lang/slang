#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() const {
		print("TestCase 1: abs(double)");

		double value = -1.23d;

		print("abs(" + value + ") = " + abs(value));

		return abs(value) == 1.23d;
	}

	private bool TestCase2() const {
		print("TestCase 2: abs(float)");

		float value = -1.23f;

		print("abs(" + value + ") = " + abs(value));

		return abs(value) == 1.23f;
	}
}

