#!/usr/local/bin/oscript

import System.Collections.Vector;
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
		Vector<Integer> vector = new Vector<Integer>();

		// Setup
		Integer item;
		vector.insert(0, new Integer(664));
		vector.insert(1, new Integer(1389));
		vector.insert(1, new Integer(173));

		// Usage
		assert( vector.size() == 3 );

		item = Integer vector.at(0);
		assert( item == 664 );

		item = Integer vector.at(1);
		assert( item == 173 );

		item = Integer vector.at(2);
		assert( item == 1389 );

		return true;
	}

	return false;
}

private bool TestCase2() const {
	print("TestCase 2: erase front");

	try {
		Vector<Integer> vector = new Vector<Integer>();

		// Setup
		Integer item;

		vector.insert(0, new Integer(664));
		vector.insert(1, new Integer(173));
		vector.insert(2, new Integer(1389));

		// Usage
		assert( vector.size() == 3 );

		vector.erase(0);

		assert( vector.size() == 2 );

		item = Integer vector.at(0);
		assert( item == 173 );

		item = Integer vector.at(1);
		assert( item == 1389 );

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
		Vector<Integer> vector = new Vector<Integer>();

		// Setup
		Integer item;

		vector.insert(0, new Integer(664));
		vector.insert(1, new Integer(173));
		vector.insert(2, new Integer(1389));

		// Usage
		assert( vector.size() == 3 );

		vector.erase(1);

		assert( vector.size() == 2 );

		item = Integer vector.at(0);
		assert( item == 664 );

		item = Integer vector.at(1);
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
	print("TestCase 4: erase back");

	try {
		Vector<Integer> vector = new Vector<Integer>();

		// Setup
		Integer item;
		vector.insert(0, new Integer(664));
		vector.insert(1, new Integer(173));
		vector.insert(2, new Integer(1389));

		// Usage
		assert( vector.size() == 3 );

		vector.erase(2);

		assert( vector.size() == 2 );

		item = Integer vector.at(0);
		assert( item == 664 );

		item = Integer vector.at(1);
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
	print("TestCase 5: iterator");

	try {
		Vector<Integer> vector = new Vector<Integer>();

		Integer item;

		vector.insert(0, new Integer(664));
		vector.insert(1, new Integer(173));
		vector.insert(2, new Integer(1389));

		assert( vector.size() == 3 );

		item = Integer vector.at(0);
		assert( item == 664 );

		item = Integer vector.at(1);
		assert( item == 173 );

		item = Integer vector.at(2);
		assert( item == 1389 );

		Iterator<Integer> it = vector.getIterator();

		while ( it.hasNext() ) {
			it.next();

			item = Integer it.current();
			//print(string item);
		}

		return true;
	}

	return false;
}

private bool TestCase6() const {
	print("TestCase 6: reverse iterator");

	try {
		Vector<String> vector = new Vector<String>();

		vector.insert(0, new String("1"));
		vector.insert(1, new String("2"));
		vector.insert(2, new String("3"));

		assert( vector.size() == 3 );

		ReverseIterator<String> it = vector.getReverseIterator();

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
		Vector<String> vector = new Vector<String>();

		vector.insert(0, new String("1"));
		vector.insert(1, new String("2"));
		vector.insert(2, new String("3"));

		assert( vector.size() == 3 );

		assert( vector.indexOf(new String("1")) == 0 );
		assert( vector.indexOf(new String("2")) == 1 );
		assert( vector.indexOf(new String("3")) == 2 );

		return true;
	}

	return false;
}

private bool TestCase8() const {
	print("TestCase 8: contains");

	try {
		Vector<Integer> vector = new Vector<Integer>();
		assert( vector is Object );
		assert( vector is ICollection );

		vector.insert(0, new Integer(1));
		vector.insert(1, new Integer(2));
		vector.insert(2, new Integer(3));

		assert( vector.size() == 3 );

		assert( vector.contains(new Integer(1)) );
		assert( vector.contains(new Integer(2)) );
		assert( vector.contains(new Integer(3)) );

		return true;
	}

	return false;
}

