#!/usr/local/bin/oscript

public namespace ExceptionTest
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
			assert( TestCase3() );
			assert( TestCase4() );
		}

		private bool TestCase1()
		{
			try {
				number one = 1;
				print("one = " + one);

				throw;

				assert( false );
			}

			return true;
		}

		private bool TestCase2()
		{
			try {
				number one = 1;
				print("one = " + one);

				throw;

				assert( false );
			}
/*
			finally {
				number one = 2;
				print("one = " + one);
			}
*/
			return true;
		}

		private bool TestCase3()
		{
			try {
				number one = 1;
				print("one = " + one);

				throw;

				assert( false );
			}
/*
			catch {
				number one = 2;
				print("one = " + one);
			}
			finally {
				number one = 3;
				print("one = " + one);
			}
*/
			return true;
		}

		private bool TestCase4()
		{
			number one = 1;
			print("one = " + one);

			throw;

			assert( false );
		}
	}
}

