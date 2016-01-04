#!/usr/local/bin/oscript

public namespace ScopeTest
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			//assert( TestCase1() );
			//assert( TestCase2() );
			assert( TestCase3() );
		}

		private bool TestCase1() const
		{
			number one = 1;
			print("one = " + one);
			{
				number one = 2;
				print("one = " + one);
			}
			print("one = " + one);

			return true;
		}

		private bool TestCase2() const
		{
			int i = 1i;
			print("i = " + i);
			{
				int i = 2i;
				print("i = " + i);
				return true;
			}
			return false;	// this should not get executed
		}

		private bool TestCase3() const
		{
			number one = 1;
			print("one = " + one);
			number two = 2;
			print("two = " + two);
			for ( int num = 0i; num < 5i; num = num + 1i; ) {
				print("num = " + num);
				print("one = " + one);
				print("two = " + two);

				{ number one = 1; number two = 2; }
				print("one = " + one);
				print("two = " + two);

				number one = 3;
				{ number one = 3; number two = 4; }
				print("one = " + one);
				print("two = " + two);

				{ number one = 5; number two = 6; }
				print("one = " + one);
				print("two = " + two);
			}
			print("one = " + one);
			print("two = " + two);
			return true;
		}
	}
}

