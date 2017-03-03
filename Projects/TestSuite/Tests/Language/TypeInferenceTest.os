#!/usr/local/bin/oscript

import System.Collections.List;
import System.Integer;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase41() );
	assert( TestCase5() );
	assert( TestCase6() );
}

private bool TestCase1() {
	print("TestCase 1: type inference with atomic type");

	int i = 1;
	var j = 2;

	print("i = " + i);
	print("j = " + j);
	print("i < j = " + (i < j));

	return i < j;
}

private bool TestCase2() {
	print("TestCase 2: type inference with reference to atomic type");

	int i = 1;
	var j = new int(2);

	print("i = " + i);
	print("j = " + j);
	print("i < j = " + (i < j));

	return i < j;
}

private bool TestCase3() {
	print("TestCase 3: type inference with atomic type constant");

	int i = 1;
	var j const = 2;

	print("i = " + i);
	print("j = " + j);
	print("i < j = " + (i < j));

	return i < j;
}

private bool TestCase4() {
	print("TestCase 4: type inference with complex type");

	Integer i = new Integer(1);
	var j = new Integer(2);

	print("i = " + i);
	print("j = " + j); 
	print("i < j = " + (i < j));
        
	return i < j;
}

private bool TestCase41() {
	print("TestCase 4.1: const type inference with complex type");

	Integer i = new Integer(1);
	var j const = new Integer(2);

	print("i = " + i);
	print("j = " + j);
	print("i < j = " + (i < j));

	return i < j;
}

private bool TestCase5() {
	print("TestCase 5: type inference during for-loop");

	for ( var i = 0; i < 5; i += 1) {
		print("i = " + i);
	}

	return i == 5;
}

private bool TestCase6() {
	print("TestCase 6: type inference during foreach-loop");

	var list = new List();
	list.push_back(Object new Integer(1));
	list.push_back(Object new Integer(2));
	list.push_back(Object new Integer(3));

	//foreach ( var i : list ) {
	foreach ( Integer i : list ) {
		print("i = " + i);
	}

	return true;
}

