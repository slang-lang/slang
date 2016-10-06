#!/usr/local/bin/oscript

import System.Collections.RandomAccessCollection;

private object TestObject {
	private int mValue;

	public void TestObject(int value) {
		mValue = value;
	}

	public string ToString() const {
		return "mValue = " + mValue;
	}
}

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
		assert( TestCase2() );
		assert( TestCase3() );
		assert( TestCase4() );
		assert( TestCase5() );
		assert( TestCase6() );
		assert( TestCase7() );
		assert( TestCase8() );
	}

	private bool TestCase1() modify {
		print("TestCase 1: insert");

		try {
			System.RandomAccessCollection list = new System.RandomAccessCollection();

			// Setup
			TestObject item;

			item = new TestObject(664);
			list.insert(Object item, 0);

			item = new TestObject(1389);
			list.insert(Object item, 1);

			item = new TestObject(173);
			list.insert(Object item, 1);

			// Usage
			assert( list.size() == 3 );

			item = list.at(0);
			assert( item.mValue == 664 );

			item = list.at(1);
			assert( item.mValue == 173 );

			item = list.at(2);
			assert( item.mValue == 1389 );

			return true;
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
			return false;
		}

		return false;
	}

	private bool TestCase2() modify {
		print("TestCase 2: erase front");

		try {
			System.RandomAccessCollection list = new System.RandomAccessCollection();

			// Setup
			TestObject item;

			item = new TestObject(664);
			list.insert(Object item, 0);

			item = new TestObject(173);
			list.insert(Object item, 1);

			item = new TestObject(1389);
			list.insert(Object item, 2);

			// Usage
			assert( list.size() == 3 );

			list.erase(0);

			assert( list.size() == 2 );

			item = list.at(0);
			assert( item.mValue == 173 );

			item = list.at(1);
			assert( item.mValue == 1389 );

			return true;
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
			return false;
		}

		return false;
	}

	private bool TestCase3() modify {
		print("TestCase 3: erase middle");

		try {
			System.RandomAccessCollection list = new System.RandomAccessCollection();

			// Setup
			TestObject item;

			item = new TestObject(664);
			list.insert(Object item, 0);

			item = new TestObject(173);
			list.insert(Object item, 1);

			item = new TestObject(1389);
			list.insert(Object item, 2);

			// Usage
			assert( list.size() == 3 );

			list.erase(1);

			assert( list.size() == 2 );

			item = list.at(0);
			assert( item.mValue == 664 );

			item = list.at(1);
			assert( item.mValue == 1389 );

			return true;
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
			return false;
		}

		return false;
	}

	private bool TestCase4() modify {
		print("TestCase 4: erase back");

		try {
			System.RandomAccessCollection list = new System.RandomAccessCollection();

			// Setup
			TestObject item;

			item = new TestObject(664);
			list.insert(Object item, 0);

			item = new TestObject(173);
			list.insert(Object item, 1);

			item = new TestObject(1389);
			list.insert(Object item, 2);

			// Usage
			assert( list.size() == 3 );

			list.erase(2);

			assert( list.size() == 2 );

			item = list.at(0);
			assert( item.mValue == 664 );

			item = list.at(1);
			assert( item.mValue == 173 );

			return true;
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
			return false;
		}

		return false;
	}

	private bool TestCase5() modify {
		print("TestCase 5: iterator");

		try {
			System.RandomAccessCollection list = new System.RandomAccessCollection();

			TestObject item;

			item = new TestObject(664);
			list.insert(Object item, 0);

			item = new TestObject(173);
			list.insert(Object item, 1);

			item = new TestObject(1389);
			list.insert(Object item, 2);

			assert( list.size() == 3 );

			item = TestObject list.at(0);
			assert( item.mValue == 664 );

			item = TestObject list.at(1);
			assert( item.mValue == 173 );

			item = TestObject list.at(2);
			assert( item.mValue == 1389 );

			System.Iterator it = list.getIterator();

			while ( it.hasNext() ) {
				it.next();

				item = it.current();
				//print(item.mValue);
			}

			return true;
		}

		return false;
	}

	private bool TestCase6() modify {
		print("TestCase 6: reverse iterator");

		try {
			System.RandomAccessCollection list = new System.RandomAccessCollection();

			list.insert(Object "1", 0);
			list.insert(Object "2", 1);
			list.insert(Object "3", 2);

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

	private bool TestCase7() modify {
		print("TestCase 7: indexOf");

		try {
			System.RandomAccessCollection list = new System.RandomAccessCollection();

			list.insert(Object "1", 0);
			list.insert(Object "2", 1);
			list.insert(Object "3", 2);

			assert( list.size() == 3 );

			assert( list.indexOf(Object "1") == 0 );
			assert( list.indexOf(Object "2") == 1 );
			assert( list.indexOf(Object "3") == 2 );

			return true;
		}

		return false;
	}

	private bool TestCase8() modify {
		print("TestCase 8: contains");

		try {
			System.RandomAccessCollection list = new System.RandomAccessCollection();
			assert( list is Object );
			assert( list is System.ACollection );

			list.insert(Object 1, 0);
			list.insert(Object 2, 1);
			list.insert(Object 3, 2);

			assert( list.size() == 3 );

			assert( list.contains(Object 1) );
			assert( list.contains(Object 2) );
			assert( list.contains(Object 3) );

			return true;
		}

		return false;
	}
}

