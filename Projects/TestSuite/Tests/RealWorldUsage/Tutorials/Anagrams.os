#!/usr/local/bin/oscript

import Scanner;
import System.Collections.List;
import System.Collections.Map;
import System.Collections.Set;
import System.IO.File;
import System.String;

public void Main(int argc, string args) {
	Map<String, Set> map = new Map<String, Set>();

	try {
		Scanner scanner = new Scanner(new System.IO.File("testfile", "r"));

		foreach ( string word : scanner ) {
			String alpha = alphabetize(word);

			Set set = map.get(alpha);
			if ( set == null ) {
				map.put(alpha, new Set());
			}
		}

		foreach ( Pair<String, Set> p : map ) {
			print("p.second.size() = " + p.second.size());
		}
	}
}

private String alphabetize(string word) {
	print("alphabetize(" + word + ")");

	Set sorted = new Set();

	foreach ( string s : word ) {
		sorted.insert(Object new String(s));
	}

	String result = new String();

	foreach ( string s : sorted ) {
		result = result + s;
	}

	return result;
}

