#!/usr/local/bin/slang

import System.Collections.List;
import System.Integer;

public void Main(int argc = 0, string args = "") const {
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

private bool TestCase1() const {
	print("TestCase 1: push_back");

	try {
		var list = new List<Integer>();

		// Setup
		list.push_back(new Integer(664));
		list.push_back(new Integer(173));
		list.push_back(new Integer(1389));

		// Usage
		assert( list.size() == 3 );

		Integer item = Integer list.at(0);
		assert( item == 664 );

		item = Integer list.at(1);
		assert( item == 173 );

		item = Integer list.at(2);
		assert( item == 1389 );

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());

		return false;
	}

	return false;
}

private bool TestCase2() const {
	print("TestCase 2: push_front");

	try {
		var list = new List<Integer>();

		list.push_front(new Integer(1389));
		list.push_front(new Integer(173));
		list.push_front(new Integer(664));

		// Usage
		assert( list.size() == 3 );

		Integer item = Integer list.at(0);
		assert( item == 664 );

		item = Integer list.at(1);
		assert( item == 173 );

		item = Integer list.at(2);
		assert( item == 1389 );

		return true;
	}

	return false;
}

private bool TestCase3() const {
	print("TestCase 3: pop_front");

	try {
		var list = new List<Integer>();

		// Setup
		list.push_back(new Integer(664));
		list.push_back(new Integer(173));
		list.push_back(new Integer(1389));

		// Usage
		assert( list.size() == 3 );

		list.pop_front();

		assert( list.size() == 2 );

		Integer item = Integer list.at(0);
		assert( item == 173 );

		item = Integer list.at(1);
		assert( item == 1389 );

		list.pop_front();

		assert( list.size() == 1 );

		item = Integer list.at(0);
		assert( item == 1389 );

		list.pop_front();

		assert( list.size() == 0 );

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());

		return false;
	}

	return false;
}

private bool TestCase4() const {
	print("TestCase 4: pop_back");

	try {
		var list = new List<Integer>();

		// Setup
		list.push_back(new Integer(664));
		list.push_back(new Integer(173));
		list.push_back(new Integer(1389));

		// Usage
		assert( list.size() == 3 );

		list.pop_back();

		assert( list.size() == 2 );

		Integer item = Integer list.at(0);
		assert( item == 664 );

		item = Integer list.at(1);
		assert( item == 173 );

		list.pop_back();

		assert( list.size() == 1 );

		item = Integer list.at(0);
		assert( item == 664 );

		list.pop_back();

		assert( list.size() == 0 );

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());

		return false;
	}

	return false;
}

private bool TestCase5() const {
	print("TestCase 5: clear");

	try {
		var list = new List<Integer>();
		assert( list );

		list.push_back(new Integer(1));
		list.push_back(new Integer(2));
		list.push_back(new Integer(3));

		assert( !list.empty() );
		assert( list.size() == 3 );

		Integer item;

		var it = list.getIterator();
/*
		while ( it.hasNext() ) {
			it.next();

			item = Integer it.current();
			//print(string item);
		}
*/
		list.clear();

		it.reset();
		while ( it.hasNext() ) {
			it.next();

			item = Integer it.current();
			//print(string item);
		}

		assert( list.empty() );
		assert( list.size() == 0 );

		return true;
	}

	return false;
}

private bool TestCase6() const {
	print("TestCase 6: native data types");

	try {
		var list = new List<string>();

		assert( list );
		assert( list is Object );

		list.push_back("1");
		list.push_back("2");
		list.push_back("3");

		assert( list.size() == 3 );

		var it = list.getIterator();
		while ( it.hasNext() ) {
			it.next();

			string value = it.current();
			//print(value);
		}

		list.clear();

		assert( list.empty() );

		return true;
	}
	catch {
		return false;
	}

	return false;
}

private bool TestCase7() const {
	print("TestCase 7: foreach");

	try {
		List<string> list = new List<string>();

		assert( list );
		assert( list is Object );

		list.push_back("1");
		list.push_back("2");
		list . push_back("3");

		assert( list.size() == 3 );

		foreach ( string s : list ) {
			//print("s = " + s);
		}

		list.clear();

		assert( list.empty() );

		return true;
	}
	catch {
		return false;
	}

	return false;
}

private bool TestCase8() const {
	print( "TestCase 8: erase and add" );

	try {
		var collection = new List<int>();

		// Set up
		collection.push_back( 1 );
		collection.push_back( 2 );
		collection.push_back( 3 );

		// Test
		assert( collection.size() == 3 );

		collection.erase( 0 );

		assert( collection.size() == 2 );
		collection.erase( 0 );
		assert( collection.size() == 1 );

		collection.erase( 0 );
		assert( collection.size() == 0 );

		collection.push_back( 4 );

		assert( collection.at( 0 ) == 4 );

		return true;
	}

	return false;
}

