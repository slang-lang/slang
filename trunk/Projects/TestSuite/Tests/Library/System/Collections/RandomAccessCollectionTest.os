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
		}

		private bool TestCase1() modify {
			print("TestCase 1: insert");

			try {
				System.RandomAccessCollection list = new System.RandomAccessCollection();

				// Setup
				TestObject item;

				item = new TestObject(0664);
				list.insert(Object item, 0);

				item = new TestObject(1389);
				list.insert(Object item, 1);

				item = new TestObject(173);
				list.insert(Object item, 1);

				// Usage
				assert( list.size() == 3 );

				while ( list.hasNext() ) {
					list.next();

					TestObject item = TestObject list.current();
					print(item.ToString());
				}

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

				while ( list.hasNext() ) {
					list.next();

					TestObject item = TestObject list.current();
					print(item.ToString());
				}

				assert( list.size() == 2 );

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

				while ( list.hasNext() ) {
					list.next();

					TestObject item = TestObject list.current();
					print(item.ToString());
				}

				assert( list.size() == 2 );

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

				while ( list.hasNext() ) {
					list.next();

					TestObject item = TestObject list.current();
					print(item.ToString());
				}

				assert( list.size() == 2 );

				return true;
			}
			catch ( System.OutOfBoundsException e ) {
				print(e.what());
				return false;
			}

			return false;
		}
}

