#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
	}

	private bool TestCase1() const {
		print("TestCase1: time()");

		int count = 0;
		int value = 0;

		while ( count < 5 ) {
			value = time();
			print("time() = " + value);

			sleep(1000);

			count++;
		}

		return value > 0;
	}
}

