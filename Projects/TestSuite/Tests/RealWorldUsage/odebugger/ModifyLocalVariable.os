#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc, string args) {
		string str = "bla";

		if ( str == "foo" ) {
			print("odebugger changed str from 'bla' to 'foo'.");
		}
		else {
			print("nothing happened.");
		}
	}
}

