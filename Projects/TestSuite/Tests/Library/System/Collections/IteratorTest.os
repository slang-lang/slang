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
		List<String> list = new List<String>();
		assert(list is ICollection);

		list.push_back(new String("1"));
		list.push_back(new String("2"));
		list.push_back(new String("3"));

		Iterator<String> it = list.getIterator();

		while ( it.hasNext() ) {
			it.next();

			//print(string it.current());
		}

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());
	}
	catch ( Exception e ) {
		print(e.what());
	}

	return false;
}

private bool TestCase2() const {
	print("TestCase 2: reverse iterate");

	try {
		List<String> list = new List<String>();
		assert(list is ICollection);

		list.push_back(new String("1"));
		list.push_back(new String("2"));
		list.push_back(new String("3"));

		ReverseIterator<String> it = list.getReverseIterator();

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
		List<String> list = new List<String>();
		assert( list is List<String> );

		list.push_back(new String("1"));
		list.push_back(new String("2"));
		list.push_back(new String("3"));

		Iterator<String> iterator = list.getIterator();
		ReverseIterator<String> reverse = list.getReverseIterator();

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
		List<String> list = new List<String>();
		assert( list is ICollection );
		assert( list is Object );

		list.push_back(new String("Item 1"));
		list.push_back(new String("Item 2"));
		list.push_back(new String("Item 3"));

		assert( list.size() == 3 );

		Iterator<String> it = list.getIterator();

		while ( it.hasNext() ) {
			it++;

			//print("it = " + it.current());
		}

		return true;
	}

	return false;
}

