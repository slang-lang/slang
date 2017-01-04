#!/usr/local/bin/oscript

import System.Collections.Iterator;
import System.Collections.List;
import System.String;

public void Main(int argc = 0, string args = "") const {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
}

private bool TestCase1() const {
	print("TestCase 1: iterate");

	try {
		List list = new List();
		assert(list is AbstractCollection);

		list.push_back(Object new String("1"));
		list.push_back(Object new String("2"));
		list.push_back(Object new String("3"));

		Iterator it = list.getIterator();

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
		List list = new List();
		assert(list is AbstractCollection);

		list.push_back(Object new String("1"));
		list.push_back(Object new String("2"));
		list.push_back(Object new String("3"));

		ReverseIterator it = list.getReverseIterator();

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
		List list = new List();
		assert( list is List );

		list.push_back(Object new String("1"));
		list.push_back(Object new String("2"));
		list.push_back(Object new String("3"));

		Iterator iterator = list.getIterator();
		ReverseIterator reverse = list.getReverseIterator();

		while ( iterator.hasNext() && reverse.hasNext() ) {
			iterator.next();
			//print("iterator = " + iterator.current());

			reverse.next();
			//print("reverse = " + reverse.current());

			//print("iterator = " + iterator.next());
			//print("reverse = " + reverse.next());
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

private bool TestCase4() const {
	print("TestCase 4: iterator operators");

	try {
		List list = new List();
		assert( list is Object );
		assert( list is AbstractCollection );

		list.push_back(Object new String("Item 1"));
		list.push_back(Object new String("Item 2"));
		list.push_back(Object new String("Item 3"));

		assert( list.size() == 3 );

		Iterator it = list.getIterator();

		while ( it.hasNext() ) {
			it++;

			//print("it = " + it.current());
		}

		return true;
	}

	return false;
}

