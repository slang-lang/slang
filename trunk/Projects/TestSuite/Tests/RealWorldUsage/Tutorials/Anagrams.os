#!/usr/local/bin/oscript

// Library imports
import System.Collections.List;
import System.Collections.Map;
import System.Collections.Set;
import System.IO.File;
import System.String;
import System.StringIterator;

// Project imports
import Scanner;

public void Main(int argc, string args) {
	Map<string, Set> map = new Map<string, Set>();

	try {
		Scanner scanner = new Scanner(new System.IO.File("data.txt", "r"), ",");

		foreach ( string word : scanner ) {
			string alpha = alphabetize(new String(word));
			//print("alpha = " + alpha);

			Set set;
			if ( map.contains(alpha) ) {
				set = map.get(alpha);
			}
			else {
				set = new Set();
				map.insert(alpha, set);
			}

			set.insert(Object new String(alpha));
		}

		foreach ( Pair<string, Set> p : map ) {
			cout((string p.first) + ", " + (string p.second) + ": [");
			foreach ( String s : p.second ) {
				cout("" + string s + " ");
			}
			cout("]");
			endl();
		}
	}
	catch ( Exception e ) {
		print("exception: " + e.what());
	}
	catch ( string e ) {
		print("exception: " + e);
	}
	catch {
		print("upsi");
	}
}

private string alphabetize(String word ref) {
	Set sorted = new Set();

	int length = word.Length();
	for ( int i = 0; i < length; i++ ) {
		sorted.insert(Object new String(word.At(i)));
	}

	word = "";
	foreach ( Object s : sorted ) {
		word = word + String s;
	}

	return string word;
}

