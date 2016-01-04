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
		}

		public bool TestCase1(number maxCount = 7) const
		{
			print("TestCase1");

			number count = 0;
			while ( count < maxCount ) {
				count = count + 1;
				print("count = " + count);
			}

			return true;
		}

		public bool TestCase2(number maxCount = 7) const
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

			return true;
		}

		public bool TestCase3() const
		{
			print("TestCase3");

			number count = 0;

			while ( count < 5 ) {
				print("count = " + count);

				if ( count == 1 ) {
					break;
				}

				count = count + 1;
			}

			return true;
		}

		public bool TestCase4() const
		{
			print("TestCase4");

			number count = 0;

			while ( count <= 5 ) {
				print("count = " + count);
				count = count + 1;

				if ( count == 2 ) {
					continue;
				}
			}

			return true;
		}
	}
}
