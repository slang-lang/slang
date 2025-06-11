#!/usr/bin/env slang

import System.Collections.Iterator;
import System.Collections.List;
import System.String;

public void Main(int argc = 0, string args = "") const {
	assert( TestCase1() );
	//assert( TestCase2() );
	assert( TestCase3() );
	//assert( TestCase4() );
	assert( TestCase5() );
	assert( TestCase6() );

	print( "passed" );
}

private bool TestCase1() const {
	print("TestCase 1: forward iterator");

	try {
		var list = new List<string>();
		assert( list is ICollection );
		assert( list is Object );

		list.push_back( "Item 1" );
		list.push_back( "Item 2" );
		list.push_back( "Item 3" );

		assert( list.size() == 3 );

		int count;
		var it = list.getIterator();
		while ( it.hasNext() ) {
			it++;
			
			print( "it = " + cast<string>( it.current() ) );
			count++;
		}

		//print( "count: " + cast<string>( count ) );
		return count == list.size();
	}

	return false;
}

private bool TestCase2() const {
	print( "TestCase 2: reverse iterator" );

	try {
		var list = new List<string>();
		assert( list is ICollection );
		assert( list is Object );

		// list.push_back( "Item 1" );
		// list.push_back( "Item 2" );
		// list.push_back( "Item 3" );

		list.push_front( "Item 3" );
		list.push_front( "Item 2" );
		list.push_front( "Item 1" );

		print( "first: " + list.first() );
		print( "last: " + list.last() );

		assert( list.size() == 3 );

		int count;
		var it = list.getReverseIterator();
		while ( it.hasNext() ) {
			it++;
			
			print( "it = " + cast<string>( it.current() ) );
			count++;
		}

		print( "count: " + cast<string>( count ) );
		return count == list.size();
	}

	return false;
}

private bool TestCase3() const {
	print( "TestCase 3: iterator operators" );

	try {
		var list = new List<String>();
		assert( list is ICollection );
		assert( list is Object );

		list.push_back( new String( "Item 1" ) );
		list.push_back( new String( "Item 2" ) );
		list.push_back( new String( "Item 3" ) );

		assert( list.size() == 3 );

		var it = list.getIterator();

		while ( it.hasNext() ) {
			it++;
			
			print( "it = " + cast<string>( it.current() ) );
		}

		return true;
	}

	return false;
}

private bool TestCase4() const {
	print( "TestCase 4: multiple iterators" );

	try {
		var list = new List<String>();
		assert( list is List<String> );

		list.push_back( new String( "1" ) );
		list.push_back( new String( "2" ) );
		list.push_back( new String( "3" ) );

		var forward = list.getIterator();
		var reverse = list.getReverseIterator();

		while ( forward.hasNext() && reverse.hasNext() ) {
			assert( forward.next() );
			print( "forward = " + cast<string>( forward.current() ) );

			assert( reverse.next() );
			print( "reverse = " + cast<string>( reverse.current() ) );
		}

		assert( !forward.hasNext() );
		assert( !reverse.hasNext() );
		return !forward.hasNext() && !reverse.hasNext();
	}
	catch ( OutOfBoundsException e ) {
		print( e.what() );
	}
	catch ( IException e ) {
		print( e.what() );
	}

	return false;
}

private bool TestCase5() const {
	print( "TestCase 5: single item" );

	try {
		var list = new List<string>();
		assert( list is List<string> );

		list.push_back( "Item 1" );

		int count;
		var forward = list.getIterator();
		while ( forward.hasNext() ) {
			assert( forward.next() );
			print( "forward = " + cast<string>( forward.current() ) );

			count++;
		}

		assert( !forward.hasNext() );
		return !forward.hasNext() && count == list.size();
	}
	catch ( OutOfBoundsException e ) {
		print( e.what() );
	}
	catch ( IException e ) {
		print( e.what() );
	}

	return false;
}

private bool TestCase6() const {
	print( "TestCase 6: empty collection" );

	try {
		var list = new List<string>();
		assert( list is List<string> );

		int count;
		var forward = list.getIterator();
		while ( forward.hasNext() ) {
			assert( forward.next() );
			print( "forward = " + cast<string>( forward.current() ) );

			count++;
		}

		assert( !forward.hasNext() );
		return !forward.hasNext() && count == list.size();
	}
	catch ( OutOfBoundsException e ) {
		print( e.what() );
	}
	catch ( IException e ) {
		print( e.what() );
	}
	catch ( string e ) {
		print( e );
	}

	return false;
}

