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
}

private bool TestCase1() const {
	print("TestCase 1: push_back");

	try {
		System.List list = new System.List();

		// Setup
		Integer item;

		item = new Integer(664);
		list.push_back(Object item);

		item = new Integer(173);
		list.push_back(Object item);

		item = new Integer(1389);
		list.push_back(Object item);

		// Usage
		assert( list.size() == 3 );

		item = Integer list.at(0);
		assert( item.mValue == 664 );

		item = Integer list.at(1);
		assert( item.mValue == 173 );

		item = Integer list.at(2);
		assert( item.mValue == 1389 );

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
		System.List list = new System.List();

		Integer item;

		item = new Integer(1389);
		list.push_front(Object item);

		item = new Integer(173);
		list.push_front(Object item);

		item = new Integer(664);
		list.push_front(Object item);

		// Usage
		assert( list.size() == 3 );

		item = Integer list.at(0);
		assert( item.mValue == 664 );

		item = Integer list.at(1);
		assert( item.mValue == 173 );

		item = Integer list.at(2);
		assert( item.mValue == 1389 );

		return true;
	}

	return false;
}

private bool TestCase3() const {
	print("TestCase 3: pop_front");

	try {
		System.List list = new System.List();

		// Setup
		Integer item;

		item = new Integer(664);
		list.push_back(Object item);

		item = new Integer(173);
		list.push_back(Object item);

		item = new Integer(1389);
		list.push_back(Object item);

		// Usage
		assert( list.size() == 3 );

		list.pop_front();

		assert( list.size() == 2 );

		item = Integer list.at(0);
		assert( item.mValue == 173 );

		item = Integer list.at(1);
		assert( item.mValue == 1389 );

		list.pop_front();

		assert( list.size() == 1 );

		item = Integer list.at(0);
		assert( item.mValue == 1389 );

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
		System.List list = new System.List();

		// Setup
		Integer item;

		item = new Integer(664);
		list.push_back(Object item);

		item = new Integer(173);
		list.push_back(Object item);

		item = new Integer(1389);
		list.push_back(Object item);

		// Usage
		assert( list.size() == 3 );

		list.pop_back();

		assert( list.size() == 2 );

		item = Integer list.at(0);
		assert( item.mValue == 664 );

		item = Integer list.at(1);
		assert( item.mValue == 173 );

		list.pop_back();

		assert( list.size() == 1 );

		item = Integer list.at(0);
		assert( item.mValue == 664 );

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
		System.List list = new System.List();

		Integer item;

		item = new Integer(1);
		list.push_back(Object item);

		item = new Integer(2);
		list.push_back(Object item);

		item = new Integer(3);
		list.push_back(Object item);

		assert( list.size() == 3 );

		System.Iterator it = list.getIterator();
		while ( it.hasNext() ) {
			it.next();

			item = Integer it.current();
			//print(item.mValue);
		}

		list.clear();

		it.reset();
		while ( it.hasNext() ) {
			it.next();

			item = Integer it.current();
			//print(item.mValue);
		}

		assert( list.empty() );
		assert( list.size() == 0 );

		return true;
	}

	return false;
}
