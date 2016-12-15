#!/usr/local/bin/oscript

import System.Collections.GenericStack;

public void Main(int argc = 1, string args = "") {
	GenericStack<string> strings = new GenericStack<string>();

	strings.push("664");
	strings.push("173");
	strings.push("1389");

	foreach ( string s : strings ) {
		print("s = " + s);
	}
}

