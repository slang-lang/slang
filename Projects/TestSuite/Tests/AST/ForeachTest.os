#!/usr/bin/env slang

import System.String;

public void Main(int argc = 1, string args = "") {
	String list = new String("1 2 3");

	foreach ( string s : list.Split() ) {
		print("s = " + s);
	}
	print("done(1)");

	foreach ( string t : list.Split() )
		print("t = " + t);
	print("done(2)");
}

