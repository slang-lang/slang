#!/usr/local/bin/oscript

import System.Collections.List;
import System.Exception;
import System.Integer;

public void Main(int argc = 0, string args = "") const {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
	//assert( TestCase6() );
}

private bool TestCase1() const {
	print("TestCase 1: push_back");

	try {
		List list = new List();

		// Setup
		list.push_back(Object new Integer(664));
		list.push_back(Object new Integer(173));
		list.push_back(Object new Integer(1389));

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
		List list = new List();

		list.push_front(Object new Integer(1389));
		list.push_front(Object new Integer(173));
		list.push_front(Object new Integer(664));

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
		List list = new List();

		// Setup
		list.push_back(Object new Integer(664));
		list.push_back(Object new Integer(173));
		list.push_back(Object new Integer(1389));

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
		List list = new List();

		// Setup
		list.push_back(Object new Integer(664));
		list.push_back(Object new Integer(173));
		list.push_back(Object new Integer(1389));

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
		List list = new List();
		assert( list );

		list.push_back(Object new Integer(1));
		list.push_back(Object new Integer(2));
		list.push_back(Object new Integer(3));

		assert( !list.empty() );
		assert( list.size() == 3 );

		Integer item;

		Iterator it = list.getIterator();
		while ( it.hasNext() ) {
			it.next();

			item = Integer it.current();
			//print(string item);
		}

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

private bool TestCase6() {
	print("TestCase 6: generic List");

	try {
		List<int> list = new List<int>();
		assert( list );

		list.push_back(1);
		list.push_back(2);
		list.push_back(3);

		assert( !list.empty() );
		assert( list.size() == 3 );

		foreach ( int i : list ) {
			print(i);
		}

		return true;
	}

	return false;
}

