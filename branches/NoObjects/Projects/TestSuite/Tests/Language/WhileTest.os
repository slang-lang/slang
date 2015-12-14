#!/usr/local/bin/oscript

public namespace Language
{
	public object Main
	{
		public void Main(Number argc = 0, String argv = "")
		{
			assert( TestCase1(5) );
		}

		public void TestCase1(Number maxCount = 7)
		{
			Number count = 0;
			while ( count < maxCount ) {
				count = count + 1;
				print("count = " & count);
			}
		}
	}
}