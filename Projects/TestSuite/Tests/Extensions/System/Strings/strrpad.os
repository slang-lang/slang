#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
	}

	private bool TestCase1() {
		print("TestCase 1: strrpad()");

		string value = "pad right";
		int length = 10;
		string pattern = ".";

		print("strrpad(" + value + ", " + length + ", \"" + pattern + "\") = " + strrpad(value, length, pattern));

		return strrpad(value, length, pattern) == "pad right..........";
	}
}

