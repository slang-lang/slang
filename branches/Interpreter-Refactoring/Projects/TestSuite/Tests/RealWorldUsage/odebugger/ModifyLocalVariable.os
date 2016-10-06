#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc, string args) {
		string str = "bla";

		if ( str != "bla" ) {
			print("odebugger changed str from 'bla' to '" + str + "'.");
		}
		else {
			print("nothing happened.");
		}
	}
}

