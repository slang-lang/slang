#!/usr/local/bin/oscript

import System.Collections.List;
import System.String;

public object Prototype<T> {
	public T mValue;

	public void Constructor(T value) {
		mValue = value;
	}
	
	public string =operator(string none) const {
		return string mValue;
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	//assert( TestCase5() );	// null pointer access
}

private bool TestCase1() {
	print("TestCase 1: valid foreach with collection");

	List<String> list = new List<String>();

	list.push_back(new String("664"));
	list.push_back(new String("173"));
	list.push_back(new String("1389"));

	assert( list.size() == 3 );

	foreach ( String s const : list ) {
		print(string s);
	}

	return true;
}

private bool TestCase2() {
	print("TestCase 2: valid foreach with collection");

	List<String> list = new List<String>();

	list.push_back(new String("664"));
	list.push_back(new String("173"));
	list.push_back(new String("1389"));

	assert( list.size() == 3 );

	foreach ( String r : list ) {
		foreach ( String s : list ) {
			foreach ( Object t : list ) {
				print(string r);
				print(string s);
				print(string t);
			}
		}
	}

	return true;
}

private bool TestCase3() {
	print("TestCase 3: foreach on String");

	String str = new String("One can iterate over a String");

	foreach ( String s : str.Split() ) {
		print("s = " + string s);
	}

	return true;
}

private bool TestCase4() {
	print("TestCase 4: valid foreach with prototype");

	List<Object> list = new List<Object>();

	list.push_back(Object new Prototype<int>(664));
	list.push_back(Object new Prototype<int>(173));
	list.push_back(Object new Prototype<int>(1389));

	assert( list.size() == 3 );

	foreach ( Prototype<int> p : list ) {
		print(string p);
	}

	return true;
}

private bool TestCase5() {
	print("TestCase 5: foreach with null reference");

	List list;
	assert( !list );

	foreach ( Object o : list ) {
		assert( !"we should never get here" );
	}
	assert( !"this should have produced a null pointer exception" );

	return false;
}

