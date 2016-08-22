#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() const {
		print("TestCase 1: strlpad()");

		string value = "pad left";
		int length = 10;
		string pattern = ".";

		print("strlpad(" + value + ", " + length + ", \"" + pattern + "\") = " + strlpad(value, length, pattern));

		return strlpad(value, length, pattern) == "..........pad left";
	}

	private bool TestCase2() const {
		print("TestCase 2: strlpad()");

		try {
			print(strlpad("bla", -2, "."));

			assert(!"we should never get here!");
		}
		catch {
			print("caught exception");
			return true;
		}

		return false;
	}
}

