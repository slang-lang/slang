#!/usr/local/bin/oscript

	public object Main
	{
		public void Main(int argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
			assert( TestCase3() );
		}

		private bool TestCase1() const
		{
			int one = 1;
			print("one = " + one);
			{
				int one = 2;
				print("one = " + one);
			}
			print("one = " + one);

			return (one == 1);
		}

		private bool TestCase2() const
		{
			int one = 1;
			print("one = " + one);
			{
				int one = 2;
				print("one = " + one);
				return true;
			}
			return false;	// this should not get executed
		}

		private bool TestCase3() const
		{
			int one = 1;
			print("one = " + one);
			int two = 2;
			print("two = " + two);
			for ( int num = 0; num < 5; num = num + 1 ) {
				print("num = " + num);
				print("one = " + one);
				print("two = " + two);

				{ int one = 1; int two = 2; }
				print("one = " + one);
				print("two = " + two);

				int one = 3;
				{ int one = 3; int two = 4; }
				print("one = " + one);
				print("two = " + two);

				{ int one = 5; int two = 6; }
				print("one = " + one);
				print("two = " + two);
			}
			print("one = " + one);
			print("two = " + two);
			return one == 1 && two == 2;
		}
	}

