#!/usr/local/bin/oscript

import System.Collections.List;
import System.Exception;

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
	}

	private bool TestCase1() modify {
		print("TestCase 1: push_back");

		try {
			System.List list = new System.List();

			// Setup
			TestObject item;

			item = new TestObject(0664);
			list.push_back(Object item);

			item = new TestObject(173);
			list.push_back(Object item);

			item = new TestObject(1389);
			list.push_back(Object item);

			// Usage
			assert( list.size() == 3 );

            item = list.at(0);
            assert( item.mValue == 0664 );

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
		print("TestCase 2: push_front");

		try {
			System.List list = new System.List();

			TestObject item;

			item = new TestObject(1389);
			list.push_front(Object item);

			item = new TestObject(173);
			list.push_front(Object item);

			item = new TestObject(664);
			list.push_front(Object item);

			// Usage
			assert( list.size() == 3 );

            item = list.at(0);
            assert( item.mValue == 0664 );

            item = list.at(1);
            assert( item.mValue == 173 );

            item = list.at(2);
            assert( item.mValue == 1389 );

			return true;
		}

		return false;
	}

	private bool TestCase3() modify {
		print("TestCase 3: pop_front");

		try {
			System.List list = new System.List();

			// Setup
			TestObject item;

			item = new TestObject(664);
			list.push_back(Object item);

			item = new TestObject(173);
			list.push_back(Object item);

			item = new TestObject(1389);
			list.push_back(Object item);

			// Usage
			assert( list.size() == 3 );

			list.pop_front();

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

	private bool TestCase4() modify {
		print("TestCase 4: pop_back");

		try {
			System.List list = new System.List();

			// Setup
			TestObject item;

			item = new TestObject(664);
			list.push_back(Object item);

			item = new TestObject(173);
			list.push_back(Object item);

			item = new TestObject(1389);
			list.push_back(Object item);

			// Usage
			assert( list.size() == 3 );

			list.pop_back();

			assert( list.size() == 2 );

            item = list.at(0);
            assert( item.mValue == 0664 );

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
}

