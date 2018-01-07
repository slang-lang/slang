#!/usr/local/bin/oscript

import System.Collections.DoubleLinkedList;
import System.Collections.Iterator;
import System.Exception;
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
	print("TestCase 1: push_back");

	try {
		DoubleLinkedList<Integer> list = new DoubleLinkedList<Integer>();

		Integer item;

		item = new Integer(173);
		list.push_back(item);

		item = new Integer(1389);
		list.push_back(item);

		// Usage
		assert( list.size() == 2 );

		item = Integer list.at(0);
		assert(item == 173);

		item = Integer list.at(1);
		assert(item == 1389);

		//item = Integer list.at(2);

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());
	}

	return false;
}

private bool TestCase2() const {
	print("TestCase 2: push_front");

	try {
		DoubleLinkedList<Integer> list = new DoubleLinkedList<Integer>();

		Integer item;
		item = new Integer(1389);
		list.push_front(item);

		item = new Integer(173);
		list.push_front(item);

		item = new Integer(664);
		list.push_front(item);

		// Usage
		assert( list.size() == 3 );

/*
		Iterator it = list.getIterator();
		while ( it.hasNext() ) {
			it.next();

			print(string it.current());
		}
*/

		item = Integer list.at(0);
		assert(item == 664);

		item = Integer list.at(1);
		assert(item == 173);

		item = Integer list.at(2);
		assert(item == 1389);

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());

		return false;
	}

	return false;
}

private bool TestCase3() const {
	print("TestCase 3: pop_front");

	try {
		DoubleLinkedList<Integer> list = new DoubleLinkedList<Integer>();

		// Setup
		Integer item;

		item = new Integer(664);
		list.push_back(item);

		item = new Integer(173);
		list.push_back(item);

		item = new Integer(1389);
		list.push_back(item);

		// Usage
		assert( list.size() == 3 );

		list.pop_front();

		assert( list.size() == 2 );

		item = Integer list.at(0);
		assert( item == 173 );

		item = Integer list.at(1);
		assert( item == 1389 );

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
		DoubleLinkedList<Integer> list = new DoubleLinkedList<Integer>();

		// Setup
		Integer item;

		item = new Integer(664);
		list.push_back(item);

		item = new Integer(173);
		list.push_back(item);

		item = new Integer(1389);
		list.push_back(item);

		// Usage
		assert( list.size() == 3 );

		list.pop_back();

		assert( list.size() == 2 );

		item = Integer list.at(0);
		assert( item == 664 );

		item = Integer list.at(1);
		assert( item == 173 );

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());

		return false;
	}

	return false;
}

private bool TestCase5() const {
	print("TestCase 5: iterate");

	try {
		DoubleLinkedList<Integer> list = new DoubleLinkedList<Integer>();

		// Setup
		Integer item;

		item = new Integer(664);
		list.push_back(item);

		item = new Integer(173);
		list.push_back(item);

		item = new Integer(1389);
		list.push_back(item);

		// Usage
		assert( list.size() == 3 );

		Iterator it = list.getIterator();

		int count = 0;
		while ( it.hasNext() ) {
			it.next();

			count++;

			Integer item = Integer it.current();
			//print("item = " + string item);
		}

		assert( count == 3 );

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());

		assert(false);
		return false;
	}

	assert(false);
	return false;
}

private bool TestCase6() const {
	print("TestCase 6: reverse iterate");

	try {
		DoubleLinkedList<Integer> list = new DoubleLinkedList<Integer>();

		// Setup
		Integer item;

		item = new Integer(664);
		list.push_back(item);

		item = new Integer(173);
		list.push_back(item);

		item = new Integer(1389);
		list.push_back(item);

		// Usage
		assert( list.size() == 3 );

		ReverseIterator it = list.getReverseIterator();

		int count = 0;
		while ( it.hasNext() ) {
			it.next();

			count++;

			Integer item = Integer it.current();
			//print(item.ToString());
		}

		assert( count == 3 );

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());

		return false;
	}

	return false;
}

private bool TestCase7() const {
	print("TestCase 7: indexOf");

	try {
		DoubleLinkedList<String> list = new DoubleLinkedList<String>();
		assert( list is Object );

		list.push_back(new String("1"));
		list.push_back(new String("2"));
		list.push_back(new String("3"));

		assert( list.size() == 3 );

		assert( list.indexOf(new String("1")) == 0 );
		assert( list.indexOf(new String("2")) == 1 );
		assert( list.indexOf(new String("3")) == 2 );

		return true;
	}

	return false;
}

private bool TestCase8() const {
	print("TestCase 8: contains");

	try {
		DoubleLinkedList<Integer> list = new DoubleLinkedList<Integer>();
		assert( list is ICollection );

		list.push_back(new Integer(1));
		list.push_back(new Integer(2));
		list.push_back(new Integer(3));

		assert( list.size() == 3 );

		assert( list.contains(new Integer(1)) );
		assert( list.contains(new Integer(2)) );
		assert( list.contains(new Integer(3)) );

		return true;
	}

	return false;
}

