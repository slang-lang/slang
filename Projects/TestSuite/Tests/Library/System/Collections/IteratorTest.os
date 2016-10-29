#!/usr/local/bin/oscript

import System.Collections.Iterator;
import System.Collections.List;
import System.String;

public void Main(int argc, string args) const {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

private bool TestCase1() const {
	print("TestCase 1: iterate");

	try {
		System.List list = new System.List();
		assert(list is System.AbstractCollection);

		list.push_back(Object new String("1"));
		list.push_back(Object new String("2"));
		list.push_back(Object new String("3"));

		System.Iterator it = list.getIterator();

		while ( it.hasNext() ) {
			it.next();

			//print(string it.current());
		}

		return true;
	}
	catch ( Exception e ) {
		print(e.what());
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());
	}

	return false;
}

private bool TestCase2() const {
	print("TestCase 2: reverse iterate");

	try {
		System.List list = new System.List();
		assert(list is System.AbstractCollection);

		list.push_back(Object new String("1"));
		list.push_back(Object new String("2"));
		list.push_back(Object new String("3"));

		System.ReverseIterator it = list.getReverseIterator();

		while ( it.hasNext() ) {
			it.next();

			//print(string it.current());
		}

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print( e.what() );
	}
	catch ( Exception e ) {
		print( e.what() );
	}

	return false;
}

private bool TestCase3() const {
	print("TestCase 3: multiple iterators");

	try {
		System.List list = new System.List();
		assert( list is System.List );

		list.push_back(Object new String("1"));
		list.push_back(Object new String("2"));
		list.push_back(Object new String("3"));

		System.Iterator iterator = list.getIterator();
		System.ReverseIterator reverse = list.getReverseIterator();

		while ( iterator.hasNext() && reverse.hasNext() ) {
			iterator.next();
			reverse.next();

			//print("iterator = " + iterator.current());
			//print("reverse = " + reverse.current());
		}

		return !iterator.hasNext() && !reverse.hasNext();
	}
	catch ( OutOfBoundsException e ) {
		print( e.what() );
	}
	catch ( Exception e ) {
		print( e.what() );
	}

	return false;
}

