#!/usr/local/bin/oscript

public namespace SwitchTest
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
		}

		private bool TestCase1() const
		{
			number one = 1;
			switch ( one ) {
				case 1: return true;
				default: return false;
			}

			return false;
		}

		private bool TestCase2() const
		{
			number one = 1;
			switch ( one + 2 ) {
				case 1: return false;
				case 2: return false;
				case 3: return true;
				default: return false;
			}

			return false;
		}
	}
}

