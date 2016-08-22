#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
	}

	private bool TestCase1() {
		print("TestCase 1: strlpad()");

		string value = "pad left";
		int length = 10;
		string pattern = ".";

		print("strlpad(" + value + ", " + length + ", \"" + pattern + "\") = " + strlpad(value, length, pattern));

		return strlpad(value, length, pattern) == "..........pad left";
	}
}

