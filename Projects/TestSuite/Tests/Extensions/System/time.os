#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
	}

	private bool TestCase1() const {
		print("TestCase1: time()");

		int value = time();
		print("time() = " + value);

		return value > 0;
	}
}

