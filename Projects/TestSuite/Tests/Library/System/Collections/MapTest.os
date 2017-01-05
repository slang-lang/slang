#!/usr/local/bin/oscript

import System.Collections.Map;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
}

private bool TestCase1() {
	print("TestCase 1: Map.insert()");

	Map<int, string> map = new Map<int, string>();
	assert( map );
	assert( map.empty() );

	map.insert(1, "String 1");
	map.insert(2, "String 2");
	map.insert(3, "String 3");

	assert( !map.empty() );
	assert( map.size() == 3 );

	foreach ( Pair<int, string> p : map ) {
		//print("p.first = " + p.first + ", p.second = " + p.second);
	}

	return true;
}

private bool TestCase2() {
	print("TestCase 2: Map.contains()");

	Map<int, string> map = new Map<int, string>();
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

	Map<int, string> map = new Map<int, string>();
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

	Map<int, string> map = new Map<int, string>();
	assert( map );
	assert( map.empty() );

	map.insert(1, "String 1");
	map.insert(2, "String 2");
	map.insert(3, "String 3");

	assert( !map.empty() );
	assert( map.size() == 3 );

	foreach ( Pair<int, string> p : map ) {
		//print("p.first = " + p.first + ", p.second = " + p.second);
	}

	//print("removing pair with key 2");
	map.remove(2);

	assert( !map.empty() );
	assert( map.size() == 2 );

	foreach ( Pair<int, string> p : map ) {
		//print("p.first = " + p.first + ", p.second = " + p.second);
	}

	return true;
}

private bool TestCase5() {
	print("TestCase 5: Map.put()");

	Map<int, string> map = new Map<int, string>();
	assert( map );
	assert( map.empty() );

	map.insert(1, "String 1");
	map.insert(2, "String 2");
	map.insert(3, "String 3");

	assert( !map.empty() );
	assert( map.size() == 3 );

	foreach ( Pair<int, string> p : map ) {
		//print("p.first = " + p.first + ", p.second = " + p.second);
	}

	map.put(2, "alternate string");

	assert( map.size() == 3 );
	assert( map.get(2) == "alternate string" );

	foreach ( Pair<int, string> p : map ) {
		//print("p.first = " + p.first + ", p.second = " + p.second);
	}

	return true;
}

