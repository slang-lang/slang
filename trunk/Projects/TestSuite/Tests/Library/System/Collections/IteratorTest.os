#!/usr/local/bin/oscript

import System.Collections.Iterator;
import System.Collections.List;

public object Main {
	public void Main(int argc, string args) {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() modify {
		print("TestCase 1: iterate");

		try {
			System.List list = new System.List();
			assert(list is System.ACollection);

			list.push_back(Object "1");
			list.push_back(Object "2");
			list.push_back(Object "3");

			System.Iterator it = list.getIterator();

			while ( it.hasNext() ) {
				it.next();

				//print(string it.current());
			}

			return true;
		}
		catch ( System.Exception e ) {
			print(e.what());
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
		}

		return false;
	}

	private bool TestCase2() modify {
		print("TestCase 2: reverse iterate");

		try {
			System.List list = new System.List();
			assert(list is System.ACollection);

			list.push_back(Object "1");
			list.push_back(Object "2");
			list.push_back(Object "3");

			System.ReverseIterator it = list.getReverseIterator();

			while ( it.hasNext() ) {
				it.next();

				//print(string it.current());
			}

			return true;
		}
		catch ( System.Exception e ) {
			print(e.what());
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
		}

		return false;
	}
}

