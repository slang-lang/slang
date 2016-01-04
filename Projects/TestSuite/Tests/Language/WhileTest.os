#!/usr/local/bin/oscript

public namespace Language
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2(5) );
		}

		public bool TestCase1(number maxCount = 7) const
		{
			number count = 0;
			while ( count < maxCount ) {
				count = count + 1;
				print("count = " + count);
			}

			return true;
		}

		public bool TestCase2(number maxCount = 7) const
		{
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
	}
}
