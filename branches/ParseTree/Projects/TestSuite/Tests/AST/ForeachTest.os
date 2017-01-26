#!/usr/local/bin/oscript

import System.Collections.List;
import System.String;
import System.StringIterator;

public void Main(int argc = 1, string args = "") {
	print("Main(" + argc + ", \"" + args + "\")");

/*
	List list = new List();

	list.push_back("664");
	list.push_back("173");
	list.push_back("1389");
*/

	String list = new String("1 2 3");

	foreach ( string s : list ) {
		print("s = " + s);
	}
}

