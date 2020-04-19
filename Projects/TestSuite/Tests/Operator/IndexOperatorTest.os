#!/usr/local/bin/slang

import System.Collections.Map;
import System.Collections.Vector;
import System.String;

private object TestObject {
	public int operator[](int index) const {
		print("operator[" + index + "]");
		return index;
	}

	public int operator[](int left, int right) const {
		print("operator[" + left + ", " + right + "]");
		return left * right;
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
}

private bool TestCase1() const {
	print("TestCase 1: index operator");

	TestObject obj = new TestObject();

	print(string obj[173]);

	return obj[173] == 173;
}

bool TestCase2() {
	print("TestCase 2: Vector.operator[]");

	Vector<String> v = new Vector<String>();
	v.insert(0, new String("index 0"));
	v.insert(1, new String("index 1"));

	print(string v[0]);
	print(string v[1]);

	//v[0] = "new value";

	print(string v[0]);
	print(v[1]);

	return true;
}

bool TestCase3() {
	print("TestCase 3: Map.operator[]");

	Map<int, String> map = new Map<int, String>();
	map.insert(0, new String("index 0"));
	map.insert(1, new String("index 1"));

	assert( map[0] == "index 0" );
	assert( "index 1" == string map[1] );

	return true;
}

bool TestCase4() {
	print("TestCase 4: operator[,]");

	TestObject obj = new TestObject();

	print("obj[2, 3] = " + obj[2, 3]);

	assert( obj[2, 3] == 6 );

	return true;
}

