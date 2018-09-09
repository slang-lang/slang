#!/usr/local/bin/oscript

import System.Collections.List;
import System.String;
import System.StringIterator;


private List<String> getList() const {
	List<String> list = new List<String>();
	list.push_back(new String("1"));
	list.push_back(new String("2"));
	list.push_back(new String("3"));

	return list;
}

public void Main(int argc, string args) {
	foreach ( String o : getList() ) {
		print("o = " + string o);
	}

	foreach ( string p : new String(args).Split() ) {
		print("p = " + p);
	}

	foreach ( string s : String("1 2 3").Split() ) {
		print("s = " + s);
	}
}

