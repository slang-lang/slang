#!/usr/local/bin/oscript

public namespace Language
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2(5) );
			assert( TestCase3() );
			assert( TestCase4() );
			assert( TestCase5() );
		}

		private bool TestCase1(number maxCount = 7) const
		{
			print("TestCase1");

			number count = 0;
			while ( count < maxCount ) {
				count = count + 1;
				print("count = " + count);
			}

			return count == maxCount;
		}

		private bool TestCase2(number maxCount = 7) const
		{
			print("TestCase2");

			number count = 0;

			number one = 1;
			print("one = " + one);

			while ( count < maxCount ) {
				count = count + 1;
				print("count = " + count);

				number one = 2;
				print("one = " + one);
			}

			print("one = " + one);

			return count == maxCount;
		}

		private bool TestCase3() const
		{
			print("TestCase3");

			number count = 0;

			while ( count < 5 ) {
				print("count = " + count);

				if ( count == 2 ) {
					break;
				}

				count = count + 1;
			}

			return count == 2;
		}

		private bool TestCase4() const
		{
			print("TestCase4");

			number count = 0;

			while ( count < 5 ) {
				print("count = " + count);
				count = count + 1;

				if ( count == 2 ) {
					continue;
				}
			}

			return true;
		}

		private bool TestCase5() const
		{
			print("TestCase5");

			number count = 0;

			while ( count < 5 ) {
				print("count = " + count);
				count = count + 1;

				if ( count == 2 ) {
					return true;
				}
			}

			return false;
		}
	}
}
