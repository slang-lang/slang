#!/usr/bin/oscript

public namespace
{
	public object Main
	{
		public void Main()
		{
			test_if();
		}

		public void test_if(Number param1 = 2)
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
		}

	}
}
