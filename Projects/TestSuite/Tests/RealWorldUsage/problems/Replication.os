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

	intList.push_back(new Integer(1));
	intList.push_back(new Integer(7));
	intList.push_back(new Integer(3));

	foreach ( int i : intList ) {
		print("i = " + i);
	}

	StringList list = new StringList();
	assert( list is ICollection );
	assert( list is Object );

	list.push_back(new String("this is a string"));
	list.push_back(new String("and another string"));

	foreach ( string s : list ) {
		print("s = " + s);
	}
}

