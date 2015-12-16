#!/usr/local/bin/oscript

public namespace Language
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1(5) );
		}

		public void TestCase1(number maxCount = 7)
		{
			number count = 0;
			while ( count < maxCount ) {
				count = count + 1;
				print("count = " + count);
			}
		}
	}
}