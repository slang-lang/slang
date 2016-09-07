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

public object Main {
	public void Main(int argc, string args) {
		assert( TestCase1() );
	}

	private bool TestCase1() modify {
		print("TestCase 1: insert");

		try {
			System.Set set = new System.Set();
			assert( set is System.ACollection );

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
}

