#!/usr/local/bin/oscript

public namespace ScopeTest
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
		}

		private bool TestCase1()
		{
			number one = 1;
			{
				number one = 2;
				print("one = " + one);
			}
			print("one = " + one);

			return true;
		}
	}
}

