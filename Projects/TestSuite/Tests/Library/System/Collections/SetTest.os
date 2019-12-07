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
	assert( TestCase5() );
	assert( TestCase6() );
}

private bool TestCase1() const {
	print("TestCase 1: Set.insert()");

	try {
		Set<TestObject> set = new Set<TestObject>();

		TestObject item;

		int count = 0;
		while ( count < 10 ) {
			//use srand(time()); for real random numbers

			item = new TestObject(int rand());
			set.insert(item);

			count++;
		}

		TestObject last;

		Iterator<TestObject> it = set.getIterator();
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
	catch ( IException e ) {
		print("Exception: " + e.what());
	}

	return false;
}

private bool TestCase2() const {
	print("TestCase 2: Set.erase()");

	try {
		Set<Integer> set = new Set<Integer>();
		assert( set is Object );

		int count = 0;
		while ( count < 10 ) {
			set.insert(new Integer(count));

			count++;
		}

		assert( set.size() == 10 );

		//print("before erase: set has " + set.size() + " item(s)");

		Iterator<Integer> it = set.getIterator();
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
	catch ( IException e ) {
		print("Exception: " + e.what());
	}

	return false;
}

private bool TestCase3() {
	print("TestCase 3: Set.clear()");

	try {
		Set<Integer> set = new Set<Integer>();
		assert( set is Object );

		int count;

		while ( count < 10 ) {
			set.insert(new Integer(count));

			count++;
		}

		assert( !set.empty() );
		assert( set.size() == 10 );

		set.clear();

		assert( set.empty() );
		assert( set.size() == 0 );

		return true;
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}

	return false;
}

private bool TestCase4() {
	print("TestCase 4: Set iterate");

	try {
		Set<Integer> set = new Set<Integer>();

		int count;
		while ( count < 10 ) {
			set.insert(new Integer(count));

			count++;
		}

		assert( !set.empty() );
		assert( set.size() == 10 );

		Iterator<Integer> it = set.getIterator();
		while ( it.hasNext() ) {
			it.next();

			//print(string it.current());
		}

		return true;
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}

	return false;
}

private bool TestCase5() {
	print("TestCase 5: native types");

	try {
		var set = new Set<int>();
		assert( set is ICollection );

		set.insert( 2 );
		set.insert( 1 );
		set.insert( 3 );

		assert( set.size() == 3 );

		int compareValue;
		var it = set.getIterator();

		while ( it.hasNext() ) {
			assert( (compareValue++) == it.next() );
		}

		return true;
	}

	return false;
}

private bool TestCase6() {
	print("TestCase 6: foreach");

	try {
		var set = new Set<int>();
		assert( set is ICollection );

		set.insert( 2 );
		set.insert( 1 );
		set.insert( 3 );

		assert( set.size() == 3 );

		int compareValue;
		var it = set.getIterator();

		foreach ( int i : set ) {
			//print("i = " + i);
		}

		return true;
	}

	return false;
}

