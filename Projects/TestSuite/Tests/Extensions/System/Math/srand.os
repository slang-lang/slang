#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
	}

	private bool TestCase1() const {
		print("TestCase 1: srand()");

		srand(17);

		int value = rand() % 10 + 1;

		print("rand() = " + value);

		return value > 0;
	}
}

