#!/usr/local/bin/oscript

import System.Collections.Stack;
import System.Exception;

public object Main {
	public void Main(int argc = 0, string args = "") {
		assert( TestCase1() );
		assert( TestCase2() );
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
}

