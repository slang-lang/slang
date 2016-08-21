#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() const {
		print("TestCase 1: ceil(double)");

		double value = 1.23d;

		print("ceil(" + value + ") = " + ceil(value));

		return ceil(value) == 2.d;
	}

	private bool TestCase2() const {
		print("TestCase 2: ceil(float)");

		float value = 1.23f;

		print("ceil(" + value + ") = " + ceil(value));

		return ceil(value) == 2.f;
	}
}

