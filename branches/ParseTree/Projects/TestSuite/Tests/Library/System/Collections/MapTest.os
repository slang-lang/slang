#!/usr/local/bin/oscript

import System.Collections.Map;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1: basic map");

	Map<int, string> map = new Map<int, string>();
	assert(map);

	assert( map.empty() );

	map.insert(1, "String 1");
	map.insert(2, "String 2");
	map.insert(3, "String 3");

	assert( !map.empty() );
	assert( map.size() == 3 );

	foreach ( Pair<int, string> p : map ) {
		print("p.first = " + p.first + ", p.second = " + p.second);
	}

	return true;
}

