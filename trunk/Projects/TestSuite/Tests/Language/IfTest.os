#!/usr/local/bin/oscript

public namespace IfTest
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
			assert( TestCase3() );
			assert( TestCase4() );
		}

		private bool TestCase1()
		{
			if ( true ) {
				print("TestCase1: true");
				assert(true);
			}

			if ( false ) {
				print("TestCase1: false");
				assert(false);
			}

			return true;
		}

		private bool TestCase2(number param1 = 2)
		{
			number one = 0;

			if ( (param1 - 1) == 0 ) {
				print("TestCase2: if-true");
				assert(false);
			}
			else if ( (param1 - 2) == 0 ) {
				print("TestCase2: else-if-true");
				assert(true);
			}
			else {
				print("TestCase2: else-if-else");
				assert(false);
			}

			one = one + 1;
			print("one = " + one);
			assert( one == 1 );
			return true;
		}

		private bool TestCase3()
		{
			// comparison operators are stickier than boolean operators
			if ( true == true && false == false ) {
				print("TestCase3: true");
				assert(true);
				return true;
			}

			print("TestCase3: false");
			assert(false);
			return false;
		}

		private bool TestCase4()
		{
			// comparison operators are stickier than boolean operators
			if ( true == (true && false) == false ) {
				print("TestCase4: true");
				assert(true);
				return true;
			}

			print("TestCase4: false");
			assert(false);
			return false;
		}
	}
}
