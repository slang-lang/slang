#!/usr/local/bin/oscript

import System.Collections.RandomAccessCollection;
import System.Integer;
import System.String;

public void Main(int argc = 0, string args = "") const {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
	assert( TestCase6() );
	assert( TestCase7() );
	assert( TestCase8() );
}

private bool TestCase1() const {
	print("TestCase 1: insert");

	try {
		System.RandomAccessCollection list = new System.RandomAccessCollection();

		// Setup
		Integer item;
		list.insert(0, Object new Integer(664));
		list.insert(1, Object new Integer(1389));
		list.insert(1, Object new Integer(173));

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

private bool TestCase2() const {
	print("TestCase 2: erase front");

	try {
		System.RandomAccessCollection list = new System.RandomAccessCollection();

		// Setup
		Integer item;

		list.insert(0, Object new Integer(664));
		list.insert(1, Object new Integer(173));
		list.insert(2, Object new Integer(1389));

		// Usage
		assert( list.size() == 3 );

		list.erase(0);

		assert( list.size() == 2 );

		item = Integer list.at(0);
		assert( item.mValue == 173 );

		item = Integer list.at(1);
		assert( item.mValue == 1389 );

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());

		return false;
	}

	return false;
}

private bool TestCase3() const {
	print("TestCase 3: erase middle");

	try {
		System.RandomAccessCollection list = new System.RandomAccessCollection();

		// Setup
		Integer item;

		list.insert(0, Object new Integer(664));
		list.insert(1, Object new Integer(173));
		list.insert(2, Object new Integer(1389));

		// Usage
		assert( list.size() == 3 );

		list.erase(1);

		assert( list.size() == 2 );

		item = Integer list.at(0);
		assert( item.mValue == 664 );

		item = Integer list.at(1);
		assert( item.mValue == 1389 );

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());

		return false;
	}

	return false;
}

private bool TestCase4() const {
	print("TestCase 4: erase back");

	try {
		System.RandomAccessCollection list = new System.RandomAccessCollection();

		// Setup
		Integer item;
		list.insert(0, Object new Integer(664));
		list.insert(1, Object new Integer(173));
		list.insert(2, Object new Integer(1389));

		// Usage
		assert( list.size() == 3 );

		list.erase(2);

		assert( list.size() == 2 );

		item = Integer list.at(0);
		assert( item.mValue == 664 );

		item = Integer list.at(1);
		assert( item.mValue == 173 );

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());

		return false;
	}

	return false;
}

private bool TestCase5() const {
	print("TestCase 5: iterator");

	try {
		System.RandomAccessCollection list = new System.RandomAccessCollection();

		Integer item;

		list.insert(0, Object new Integer(664));
		list.insert(1, Object new Integer(173));
		list.insert(2, Object new Integer(1389));

		assert( list.size() == 3 );

		item = Integer list.at(0);
		assert( item.mValue == 664 );

		item = Integer list.at(1);
		assert( item.mValue == 173 );

		item = Integer list.at(2);
		assert( item.mValue == 1389 );

		System.Iterator it = list.getIterator();

		while ( it.hasNext() ) {
			it.next();

			item = Integer it.current();
			//print(item.mValue);
		}

		return true;
	}

	return false;
}

private bool TestCase6() const {
	print("TestCase 6: reverse iterator");

	try {
		System.RandomAccessCollection list = new System.RandomAccessCollection();

		list.insert(0, Object new String("1"));
		list.insert(1, Object new String("2"));
		list.insert(2, Object new String("3"));

		assert( list.size() == 3 );

		System.ReverseIterator it = list.getReverseIterator();

		while ( it.hasNext() ) {
			it.next();

			//print(it.current());
		}

		return true;
	}

	return false;
}

private bool TestCase7() const {
	print("TestCase 7: indexOf");

	try {
		System.RandomAccessCollection list = new System.RandomAccessCollection();

		list.insert(0, Object new String("1"));
		list.insert(1, Object new String("2"));
		list.insert(2, Object new String("3"));

		assert( list.size() == 3 );

		assert( list.indexOf(Object new String("1")) == 0 );
		assert( list.indexOf(Object new String("2")) == 1 );
		assert( list.indexOf(Object new String("3")) == 2 );

		return true;
	}

	return false;
}

private bool TestCase8() const {
	print("TestCase 8: contains");

	try {
		System.RandomAccessCollection list = new System.RandomAccessCollection();
		assert( list is Object );
		assert( list is System.AbstractCollection );

		list.insert(0, Object new Integer(1));
		list.insert(1, Object new Integer(2));
		list.insert(2, Object new Integer(3));

		assert( list.size() == 3 );

		assert( list.contains(Object new Integer(1)) );
		assert( list.contains(Object new Integer(2)) );
		assert( list.contains(Object new Integer(3)) );

		return true;
	}

	return false;
}

