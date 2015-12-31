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
			}

			if ( false ) {
				print("TestCase1: false");
			}

			return true;
		}

		private bool TestCase2(number param1 = 2)
		{
			if ( (param1 - 1) == 0 ) {
				assert(false);
				print("TestCase2: if-true");
			}
			else {
				if ( (param1 - 2) == 0 ) {
					print("TestCase2: else-if-true");
				}
				else {
					assert(false);
					print("TestCase2: else-if-else");
				}
			}

			return true;
		}

		private bool TestCase3()
		{
			// comparison operators are stickier than boolean operators
			if ( true == true && false == false ) {
				print("TestCase3: true");
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
				return true;
			}

			print("TestCase4: false");
			assert(false);
			return false;
		}
	}
}
