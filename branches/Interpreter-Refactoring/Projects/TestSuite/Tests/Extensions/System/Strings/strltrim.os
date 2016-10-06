#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
	}

	private bool TestCase1() {
		print("TestCase 1: strltrim()");

		string value = "   left trim   ";
		print("strltrim(\"" + value + "\") = \"" + strltrim(value) + "\"");

		return strltrim(value) == "left trim   ";
	}
}

