#!/usr/local/bin/oscript

import System.StringIterator;

public object Main {
	public void Main(int argc, string args) {
		assert( TestCase1() );
		assert( TestCase2() );
	}

	private bool TestCase1() modify {
		print("TestCase 1: valid iteration");

		StringIterator strIt = new StringIterator("This is a string", " ");

		int count;
		while ( strIt.HasNext() && count < 10 ) {
			string next = strIt.GetNext();
			print("str.GetNext() = " + next);

			count = count++;
		}

		return true;
	}

	private bool TestCase2() modify {
		print("TestCase 2: invalid interation");

		StringIterator strIt = new StringIterator("This is a string", " ");

		try {
			int count;
			string str;
			//while ( str = strIt.GetNext() ) {
			while ( count < 10 ) {
				//print("strIt.GetNext() = " + strIt.GetNext());
				string str = strIt.GetNext();
				print("strIt.GetNext() = " + str);

				count = count++;
			}

			assert(!"we should not get here!");
			return false;
		}
		catch {
			print("caught out of bounds execption");
			return true;
		}
	}
}

