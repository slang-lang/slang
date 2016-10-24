#!/usr/local/bin/oscript

import System.Collections.Set;
import System.Exception;
import System.Math;

public object TestObject {
	private int mValue;

	public void TestObject(int value) {
		mValue = value;
	}

	public bool operator<(TestObject other ref) const {
		return mValue < other.mValue;
	}

	public bool operator<=(TestObject other ref) const {
		return mValue <= other.mValue;
	}

	public bool operator==(TestObject other ref) const {
		return mValue == other.mValue;
	}
}

public void Main(int argc, string args) modify {
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1() modify {
	print("TestCase 1: insert");

	try {
		System.Set set = new System.Set();
		assert( set is System.AbstractCollection );

		TestObject item;

		int count = 0;
		while ( count < 10 ) {
			item = new TestObject(int Math.rand());
			set.insert(Object item);

			count++;
		}

		TestObject last;

		System.Iterator it = set.getIterator();
		while ( it.hasNext() ) {
			it.next();

			item = TestObject it.current();
			//print(item.mValue);

			if ( last ) {
				assert( last <= item );
			}

			last = item;
		}

		return true;
	}

	return false;
}

private bool TestCase2() modify {
	print("TestCase 2: erase");

	try {
		System.Set set = new System.Set();
		assert( set is Object );

		int count = 0;
		while ( count < 10 ) {
			set.insert(Object count);

			count++;
		}

		System.Iterator it = set.getIterator();
		while ( it.hasNext() ) {
			it.next();

			//print(it.current());
		}

		while ( !set.empty() ) {
			try {
				set.erase(Math.rand() % 10);
				//print("set.erase");
			}

			it.reset();
			while ( it.hasNext() ) {
				it.next();

				//print(it.current());
			}
		}

		return true;
	}

	return false;
}

