#!/usr/local/bin/oscript

public namespace
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
		}

		public bool TestCase1(number param1 = 2)
		{
			if ( true ) {
				print("true");
			}

			if ( false ) {
				print("false");
			}

			if ( param1 - 1 == 0 ) {
				print("if: true");
			}
			else if ( param1 - 2 < 0 ) {
				print("else if: true");
			}
			else {
				print("else if: else");
			}

			return true;
		}
	}
}
