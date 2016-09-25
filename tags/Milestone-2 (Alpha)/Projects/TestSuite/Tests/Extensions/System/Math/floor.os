#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() const {
		print("TestCase 1: floor(double)");

		double value = 1.23d;

		print("floor(" + value + ") = " + floor(value));

		return floor(value) == 1.d;
	}

	private bool TestCase2() const {
		print("TestCase 2: floor(float)");

		float value = 1.23f;

		print("floor(" + value + ") = " + floor(value));

		return floor(value) == 1.f;
	}
}

