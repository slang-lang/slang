#!/usr/local/bin/oscript

import System.Collections.Vector;
import System.String;

private object TestObject {
	public int operator[](int index) const {
		return index;
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() const {
	print("TestCase 1: index operator");

	TestObject obj = new TestObject();

	print(string obj[173]);

	return obj[173] == 173;
}

bool TestCase2() {
	print("TestCase 2: Vector.operator[]");

	Vector v = new Vector();
	v.insert(0, Object new String("index 0"));
	v.insert(1, Object new String("index 1"));

	print(string v[0]);
	print(string v[1]);

	//v[0] = "new value";

	print(string v[0]);
	print(v[1]);

	return true;
}

