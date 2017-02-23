#!/usr/local/bin/oscript

import System.Collections.List;
import System.String;
import System.StringIterator;

public void Main(int argc = 1, string args = "") {
	print("Main(" + argc + ", \"" + args + "\")");

/*
	List objList = new List();

	objList.push_back(Object new String("664"));
	objList.push_back(Object new String("173"));
	objList.push_back(Object new String("1389"));

	foreach ( String l : objList ) {
		print("l = " + l);
	}
*/

	String list = new String("1 2 3");

	foreach ( string s : list ) {
		print("s = " + s);
	}
	print("done(1)");

	foreach ( string t : list )
		print("t = " + t);
	print("done(2)");
}

