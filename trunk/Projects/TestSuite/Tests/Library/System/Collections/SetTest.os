#!/usr/local/bin/oscript

import System.Collections.Set;
import System.Exception;
import System.Math;
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
}

private bool TestCase1() const {
	print("TestCase 1: insert");

	try {
		System.Set set = new System.Set();
		assert( set is System.AbstractCollection );

		TestObject item;

		int count = 0;
		while ( count < 10 ) {
			//use Math.srand(time()); for real random numbers

			item = new TestObject(int Math.rand());
			set.insert(Object item);

			count++;
		}

		TestObject last;

		System.Iterator it = set.getIterator();
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
	print("TestCase 2: erase");

	try {
		System.Set set = new System.Set();
		assert( set is Object );

		int count = 0;
		while ( count < 10 ) {
			set.insert(Object new Integer(count));

			count++;
		}

		assert( set.size() == 10 );

		//print("before erase: set has " + set.size() + " item(s)");

		System.Iterator it = set.getIterator();
		while ( it.hasNext() ) {
			it.next();

			//print("item = " + it.current());
		}

		while ( !set.empty() ) {
			try {
				Math.srand(time());
				set.erase(Math.rand() % set.size());
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

