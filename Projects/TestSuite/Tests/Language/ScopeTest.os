#!/usr/local/bin/oscript

public namespace ScopeTest
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
			//assert( TestCase3() );
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
			for ( number one = 2; one < 5; one = one + 1 ) {
				print("one = " + one);
				assert(one != 1);
			}
			return true;
		}
	}
}

