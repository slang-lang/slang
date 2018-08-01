#!/usr/local/bin/oscript

import System.Collections.List;
import System.Integer;
import System.String;


public object IntegerList replicates List<Integer>;
public object StringList replicates List<String>;


public void Main(int argc, string args) {
	IntegerList intList = new IntegerList();
	assert( intList is ICollection );
	assert( intList is Object );
	assert( !(intList is List<Integer>) );

	intList.push_back(new Integer(1));
	intList.push_back(new Integer(7));
	intList.push_back(new Integer(3));

	foreach ( int i : intList ) {
		print("i = " + string i);
	}

	StringList stringList = new StringList();
	assert( stringList is ICollection );
	assert( stringList is Object );
	assert( !(stringList is List<String>) );

	stringList.push_back(new String("this is a string"));
	stringList.push_back(new String("and another string"));

	foreach ( String s : stringList ) {
		print("s = " + string s);

		foreach ( string word : s ) {
			print("word = " + word);
		}
	}
}

