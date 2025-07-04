#!/usr/bin/env slang

import System.Collections.Map;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
	assert( TestCase6() );
	assert( TestCase7() );
	assert( TestCase8() );

	print( "passed" );
}

private bool TestCase1() {
	print("TestCase 1: Map.insert()");

	var map = new Map<int, string>();
	assert( map );
	assert( map.empty() );

	map.insert(1, "String 1");
	map.insert(2, "String 2");
	map.insert(3, "String 3");

	assert( !map.empty() );
	assert( map.size() == 3 );

	foreach ( Pair<int, string> p : map ) {
		//print("p = " + string p);
	}

	return true;
}

private bool TestCase2() {
	print("TestCase 2: Map.contains()");

	var map = new Map<int, string>();
	assert( map );
	assert( map.empty() );

	map.insert(1, "String 1");
	map.insert(2, "String 2");
	map.insert(3, "String 3");

	assert( !map.empty() );
	assert( map.size() == 3 );

	return map.contains(1) && map.contains(2) && map.contains(3);
}

private bool TestCase3() {
	print("TestCase 3: Map.get()");

	var map = new Map<int, string>();
	assert( map );
	assert( map.empty() );

	map.insert(1, "String 1");
	map.insert(2, "String 2");
	map.insert(3, "String 3");

	assert( !map.empty() );
	assert( map.size() == 3 );

	//print(map.get(1));
	assert( map.get(1) == "String 1" );

	return true;
}

private bool TestCase4() {
	print("TestCase 4: Map.remove()");

	var map = new Map<int, string>();
	assert( map );
	assert( map.empty() );

	map.insert(1, "String 1");
	map.insert(2, "String 2");
	map.insert(3, "String 3");

	assert( !map.empty() );
	assert( map.size() == 3 );

	foreach ( Pair<int, string> p : map ) {
		//print("p = " + string p);
	}

	//print("removing pair with key 2");
	map.remove(2);

	assert( !map.empty() );
	assert( map.size() == 2 );

	foreach ( Pair<int, string> s : map ) {
		//print("s = " + string s);
	}

	return true;
}

private bool TestCase5() {
	print("TestCase 5: Map.put()");

	var map = new Map<int, string>();
	assert( map );
	assert( map.empty() );

	map.insert(1, "String 1");
	map.insert(2, "String 2");
	map.insert(3, "String 3");

	assert( !map.empty() );
	assert( map.size() == 3 );

	foreach ( Pair<int, string> p : map ) {
		//print("p = " + string p);
	}

	map.put(2, "alternate string");

	assert( map.size() == 3 );
	assert( map.get(2) == "alternate string" );

	foreach ( Pair<int, string> s : map ) {
		//print("s = " + string s);
	}

	return true;
}

private bool TestCase6() {
	print("TestCase 6: Map.clear()");

	var map = new Map<int, string>();
	assert( map );
	assert( map.empty() );

	map.insert(1, "String 1");
	map.insert(3, "String 3");
	map.insert(2, "String 2");

	assert( !map.empty() );
	assert( map.size() == 3 );

	foreach ( Pair<int, string> p : map ) {
		//print("p = " + string p);
	}

	map.clear();
	assert( map.empty() );
	assert( map.size() == 0 );

	return true;
}

private bool TestCase7() {
	print("TestCase 7: Map iterate");

	Map<string, string> map = new Map<string, string>();
	assert( map );
	assert( map.empty() );

	map.insert("bcd", "bcd");
	map.insert("abc", "abc");
	map.insert("cde", "cde");

	assert( !map.empty() );
	assert( map.size() == 3 );

	foreach ( Pair<string, string> p : map ) {
		//print("p = " + string p);
	}

	var it = map.getIterator();
	while ( it.hasNext() ) {
		it.next();

		//print("it.current() = " + it.current());
	}

	return true;
}

private bool TestCase8() {
	print("TestCase 8: Map.operator[]");

	var map = new Map<int, string>();

	map.insert(0, "0");
	map.insert(1, "1");
	map.insert(2, "2");

	assert( map.size() == 3 );

	foreach ( Pair<int, string> p : map ) {
		//print("p = " + string p);
	}

	assert( map[0] == "0" );
	assert( map[2] == "2" );
	assert( map[1] == "1" );

	return true;
}

