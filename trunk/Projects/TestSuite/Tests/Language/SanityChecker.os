#!/usr/local/bin/oscript

public namespace SanityCheckerTest
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
		}

		private bool TestCase1() const
		{
			{
				number one = 1;

			return false;
		}

		private bool TestCase3() const
		{
			string bla = "bla bla;

			return false;
		}
	}
}

