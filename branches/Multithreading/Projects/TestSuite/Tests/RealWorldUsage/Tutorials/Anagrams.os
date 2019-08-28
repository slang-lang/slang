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

private object StringSet replicates Set<String>;


public void Main(int argc, string args) {
	Map<string, StringSet> map = new Map<string, StringSet>();

	try {
		Scanner scanner = new Scanner(new System.IO.File("data.txt", "r"), ",");

		foreach ( string word : scanner ) {
			string alpha = alphabetize(new String(word));

			StringSet set;
			if ( map.contains(alpha) ) {
				set = map.get(alpha);
			}
			else {
				set = new StringSet();
				map.insert(alpha, set);
			}

			set.insert(new String(alpha));
		}

		foreach ( Pair<string, StringSet> p : map ) {
			cout((string p.first) + ": [");
			foreach ( String s : p.second ) {
				cout("" + string s + " ");
			}
			cout("]");
			endl();
		}
	}
	catch ( IException e ) {
		print("exception: " + e.what());
	}
	catch ( string e ) {
		print("exception: " + e);
	}
	catch {
		print("upsi");
	}
}

private string alphabetize(String word) {
	StringSet sorted = new StringSet();

	int length = word.Length();
	for ( int i = 0; i < length; i++ ) {
		sorted.insert(new String(word.CharAt(i)));
	}

	word = "";
	foreach ( String s : sorted ) {
		word += s;
	}

	return string word;
}

