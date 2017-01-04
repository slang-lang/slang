#!/usr/local/bin/oscript

import System.Collections.Pair;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() {
	print("TestCase 1: basics");

	Pair<int, string> p = new Pair<int, string>(1, "Pair 1");
	assert( p );
	assert( p is Object );

	return p.first == 1 && p.second == "Pair 1";
}

