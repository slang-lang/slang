#!/usr/local/bin/oscript

public namespace SwitchTest
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
		}

		private bool TestCase1() const
		{
			number one = 1;
			switch ( one ) {
				case 1: return true;
				default: return false;
			}

			return true;
		}
	}
}

