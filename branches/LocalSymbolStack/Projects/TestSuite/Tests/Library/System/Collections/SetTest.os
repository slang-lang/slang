#!/usr/local/bin/oscript

import System.Collections.Set;
import System.Exception;
import System.Integer;

public object TestObject {
	public int mValue;

	public void Constructor(int value) {
		mValue = value;
	}

	public bool operator<(TestObject other ref) const {
		return mValue < other.mValue;
	}
	public bool operator<(int other) const {
		return mValue < other;
	}

	public bool operator<=(TestObject other ref) const {
		return mValue <= other.mValue;
	}
	public bool operator<=(int other) const {
		return mValue <= other;
	}

	public bool operator==(TestObject other ref) const {
		return mValue == other.mValue;
	}
	public bool operator==(int other) const {
		return mValue == other;
	}

	public string =operator(string none) const {
		return string mValue;
	}
}

public void Main(int argc = 0, string args = "") const {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
}

private bool TestCase1() const {
	print("TestCase 1: Set.insert()");

	try {
		Set set = new Set();
		assert( set is AbstractCollection );

		TestObject item;

		int count = 0;
		while ( count < 10 ) {
			//use srand(time()); for real random numbers

			item = new TestObject(int rand());
			set.insert(Object item);

			count++;
		}

		TestObject last;

		Iterator it = set.getIterator();
		while ( it.hasNext() ) {
			it.next();

			item = TestObject it.current();
			//print(item);

			if ( last ) {
				assert( last <= item );
			}

			last = item;
		}

		return set.size() == 10;
	}

	return false;
}

private bool TestCase2() const {
	print("TestCase 2: Set.erase()");

	try {
		Set set = new Set();
		assert( set is Object );

		int count = 0;
		while ( count < 10 ) {
			set.insert(Object new Integer(count));

			count++;
		}

		assert( set.size() == 10 );

		//print("before erase: set has " + set.size() + " item(s)");

		Iterator it = set.getIterator();
		while ( it.hasNext() ) {
			it.next();

			//print("item = " + it.current());
		}

		while ( !set.empty() ) {
			try {
				srand(time());
				set.erase(rand() % set.size());
			}
			catch ( OutOfBoundsException e ) {
				print(e.what());
			}

			//print("after erase: set has " + set.size() + " item(s)");

			it.reset();
			while ( it.hasNext() ) {
				it.next();

				//print(string it.current());
			}
		}

		return set.empty();
	}

	return false;
}

private bool TestCase3() {
	print("TestCase 3: Set.clear()");

	try {
		Set set = new Set();
		assert( set is Object );

		int count;

		while ( count < 10 ) {
			set.insert(Object new Integer(count));

			count++;
		}

		assert( !set.empty() );
		assert( set.size() == 10 );

		set.clear();

		assert( set.empty() );
		assert( set.size() == 0 );

		return true;
	}

	return false;
}

private bool TestCase4() {
	print("TestCase 4: Set iterate");

	try {
		Set set = new Set();

		int count;
		while ( count < 10 ) {
			set.insert(Object new Integer(count));

			count++;
		}

		assert( !set.empty() );
		assert( set.size() == 10 );

		Iterator it = set.getIterator();
		while ( it.hasNext() ) {
			it.next();

			//print(string it.current());
		}

		return true;
	}

	return false;
}
