#!/usr/local/bin/oscript

import System.Collections.Pair;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

private bool TestCase1() {
	print("TestCase 1: basics");

	Pair<int, string> p = new Pair<int, string>(1, "Pair 1");
	assert( p );
	assert( p is Object );

	return p.first == 1 && p.second == "Pair 1";
}

private bool TestCase2() {
	print("TestCase 2: operator<");

	Pair<int, string> p1 = new Pair<int, string>(1, "Pair 1");
	Pair<int, string> p2 = new Pair<int, string>(2, "Pair 2");

	return p1 < p2;
}

private bool TestCase3() {
	print("TestCase 3: string.operator<");

	Pair<string, string> p1 = new Pair<string, string>("abc", "Pair 1");
	Pair<string, string> p2 = new Pair<string, string>("def", "Pair 2");

	return p1 < p2;
}

