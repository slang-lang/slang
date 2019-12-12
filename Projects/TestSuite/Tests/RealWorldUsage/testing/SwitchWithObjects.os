#!/usr/local/bin/oscript

import System.String;


private object Complex extends String {
	public void Constructor(string str) {
		base.Constructor(str);

		print("mValue = " + str);
	}
}

public void Main(int, string) {
	var str = new String("1");

	print("first switch:");

	switch ( str ) {
		case "1": { print("1"); break; }
		case "2": { print("2"); break; }
		default: { print("default"); break; }
	}

	print("second switch:");

	switch ( str ) {
		case new Complex("2"): { print("2"); break; }
		case new Complex("1"): { print("1"); break; }
		default: { print("default"); break; }
	}
}

