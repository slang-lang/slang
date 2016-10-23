#!/usr/local/bin/oscript

import System.Collections.Stack;
import System.Exception;

	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
		assert( TestCase2() );
		assert( TestCase3() );
		assert( TestCase4() );
		assert( TestCase5() );
		assert( TestCase6() );
	}

	private bool TestCase1() modify {
		print("TestCase 1: push");

		try {
			System.Stack stack = new System.Stack();

			// Setup
			string item;

			item = "664";
			stack.push(Object item);

			item = "173";
			stack.push(Object item);

			item = "1389";
			stack.push(Object item);

			// Usage
			assert( stack.size() == 3 );

			item = stack.at(0);
			assert( item == "664" );

			item = stack.at(1);
			assert( item == "173" );

			item = stack.at(2);
			assert( item == "1389" );

			return true;
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
			return false;
		}

		return false;
	}

	private bool TestCase2() modify {
		print("TestCase 2: pop");

		try {
			System.Stack stack = new System.Stack();

			// Setup
			string item;

			item = "664";
			stack.push(Object item);

			item = "173";
			stack.push(Object item);

			item = "1389";
			stack.push(Object item);

			// Usage
			assert( stack.size() == 3 );

			item = stack.at(0);
			assert( item == "664" );

			item = stack.at(1);
			assert( item == "173" );

			item = stack.at(2);
			assert( item == "1389");

			stack.pop();

			assert( stack.size() == 2 );

			item = stack.at(0);
			assert( item == "664" );

			item = stack.at(1);
			assert( item == "173" );

			stack.pop();

			assert( stack.size() == 1 );

			item = stack.at(0);
			assert( item == "664" );

			stack.pop();

			assert( stack.size() == 0 );
			assert( stack.empty() );

			return true;
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
			return false;
		}

		return false;
	}

	private bool TestCase3() modify {
		print("TestCase 3: iterate");

		try {
			System.Stack stack = new System.Stack();

			stack.push(Object "1");
			stack.push(Object "2");
			stack.push(Object "3");

			assert( stack.size() == 3 );

			System.Iterator it = stack.getIterator();

			it.next();
			assert( it.current() == "1" );

			it.next();
			assert( it.current() == "2" );

			it.next();
			assert( it.current() == "3" );

			it.reset();
			while ( it . hasNext() ) {
				it.next();

				//print(it.current());
			}

			return true;
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
		}

		return false;
	}

	private bool TestCase4() modify {
		print("TestCase 4: reverse iterate");

		try {
			System.Stack stack = new System.Stack();

			stack.push(Object "1");
			stack.push(Object "2");
			stack.push(Object "3");

			assert( stack.size() == 3 );

			System.Iterator it = stack.getReverseIterator();

			it.next();
			assert( it.current() == "3" );

			it.next();
			assert( it.current() == "2" );

			it.next();
			assert( it.current() == "1" );

			it.reset();
			while ( it.hasNext() ) {
				it.next();

				//print(it.current());
			}

			return true;
		}
		
		return false;
	}

	private bool TestCase5() modify {
		print("TestCase 5: indexOf");

		try {
			System.Stack stack = new System.Stack();

			stack.push(Object "1");
			stack.push(Object "2");
			stack.push(Object "3");

			assert( stack.size() == 3 );

			assert( stack.indexOf(Object "1") == 0 );
			assert( stack.indexOf(Object "2") == 1 );
			assert( stack.indexOf(Object "3") == 2 );

			return true;
		}

		return false;
	}

	private bool TestCase6() modify {
		print("TestCase 6: contains");

		try {
			System.Stack stack = new System.Stack();
			assert( stack is Object );
			assert( stack is System.ACollection );

			stack.push(Object 1);
			stack.push(Object 2);
			stack.push(Object 3);

			assert( stack.size() == 3 );

			assert( stack.contains(Object 1) );
			assert( stack.contains(Object 2) );
			assert( stack.contains(Object 3) );

			return true;
		}

		return false;
	}

