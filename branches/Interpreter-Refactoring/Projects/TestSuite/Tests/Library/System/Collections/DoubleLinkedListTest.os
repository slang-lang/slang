#!/usr/local/bin/oscript

import System.Collections.DoubleLinkedList;
import System.Collections.Iterator;
import System.Exception;
import System.Integer;
import System.String;

	public void Main(int argc = 0, string args = "") modify {
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
		print("TestCase 1: push_back");

		try {
			System.DoubleLinkedList list = new System.DoubleLinkedList();

			Integer item;
			item = new Integer(173);
			list.push_back(Object item);

			item = new Integer(1389);
			list.push_back(Object item);

			// Usage
			assert( list.size() == 2 );

			item = Integer list.at(0);
			assert(item.mValue == 173);

			item = Integer list.at(1);
			assert(item.mValue == 1389);

			return true;
		}
		catch ( OutOfBoundsException e ) {
			print(e.what());

			return false;
		}

		return false;
	}

	private bool TestCase2() modify {
		print("TestCase 2: push_front");

		try {
			System.DoubleLinkedList list = new System.DoubleLinkedList();

			Integer item;
			item = new Integer(1389);
			list.push_back(Object item);

			item = new Integer(173);
			list.push_back(Object item);

			item = new Integer(664);
			list.push_front(Object item);

			// Usage
			assert( list.size() == 3 );

			item = Integer list.at(0);
			print("item.mValue = " + item.mValue);
			assert(item.mValue == 664);

			item = Integer list.at(1);
			print("item.mValue = " + item.mValue);
			//assert(item.mValue == 173);

			item = Integer list.at(2);
			print("item.mValue = " + item.mValue);
			//assert(item.mValue == 1389);

			return true;
		}
		catch ( OutOfBoundsException e ) {
			print(e.what());

			return false;
		}

		return false;
	}

	private bool TestCase3() modify {
		print("TestCase 3: pop_front");

		try {
			System.DoubleLinkedList list = new System.DoubleLinkedList();

			// Setup
			Integer item;

			item = new Integer(664);
			list.push_back(Object item);

			item = new Integer(173);
			list.push_back(Object item);

			item = new Integer(1389);
			list.push_back(Object item);

			// Usage
			assert( list.size() == 3 );

			list.pop_front();

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

	private bool TestCase4() modify {
		print("TestCase 4: pop_back");

		try {
			System.DoubleLinkedList list = new System.DoubleLinkedList();

			// Setup
			Integer item;

			item = new Integer(664);
			list.push_back(Object item);

			item = new Integer(173);
			list.push_back(Object item);

			item = new Integer(1389);
			list.push_back(Object item);

			// Usage
			assert( list.size() == 3 );

			list.pop_back();

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

	private bool TestCase5() modify {
		print("TestCase 5: iterate");

		try {
			System.DoubleLinkedList list = new System.DoubleLinkedList();

			// Setup
			Integer item;

			item = new Integer(664);
			list.push_back(Object item);

			item = new Integer(173);
			list.push_back(Object item);

			item = new Integer(1389);
			list.push_back(Object item);

			// Usage
			assert( list.size() == 3 );

			System.Iterator it = list.getIterator();

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

	private bool TestCase6() modify {
		print("TestCase 6: reverse iterate");

		try {
			System.DoubleLinkedList list = new System.DoubleLinkedList();

			// Setup
			Integer item;

			item = new Integer(664);
			list.push_back(Object item);

			item = new Integer(173);
			list.push_back(Object item);

			item = new Integer(1389);
			list.push_back(Object item);

			// Usage
			assert( list.size() == 3 );

			System.ReverseIterator it = list.getReverseIterator();

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

	private bool TestCase7() modify {
		print("TestCase 7: indexOf");

		try {
			System.DoubleLinkedList list = new System.DoubleLinkedList();
			assert( list is Object );

			list.push_back(Object new String("1"));
			list.push_back(Object new String("2"));
			list.push_back(Object new String("3"));

			assert( list.size() == 3 );

			assert( list.indexOf(Object new String("1")) == 0 );
			assert( list.indexOf(Object new String("2")) == 1 );
			assert( list.indexOf(Object new String("3")) == 2 );

			return true;
		}

		return false;
	}

	private bool TestCase8() modify {
		print("TestCase 8: contains");

		try {
			System.DoubleLinkedList list = new System.DoubleLinkedList();
			assert( list is System.AbstractCollection );

			list.push_back(Object new Integer(1));
			list.push_back(Object new Integer(2));
			list.push_back(Object new Integer(3));

			assert( list.size() == 3 );

			assert( list.contains(Object new Integer(1)) );
			assert( list.contains(Object new Integer(2)) );
			assert( list.contains(Object new Integer(3)) );

			return true;
		}

		return false;
	}

