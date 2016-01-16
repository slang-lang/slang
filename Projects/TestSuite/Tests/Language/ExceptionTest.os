#!/usr/local/bin/oscript

public namespace ExceptionTest
{
	private object ObjectThatThrows
	{
		public void ObjectThatThrows()
		{
		}

		public void MethodThatThrows()
		{
			print("MethodThatThrows()");

			throw;
		}
	}

	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
			assert( TestCase3() );
			assert( TestCase4() );
			assert( TestCase5() );
		}

		private bool TestCase1()
		{
			print("TestCase1()");

			try {
				print("try");

				number one = 1;
				print("one = " + one);

				throw;

				assert( false );
			}
			finally {
				print("finally");
			}

			return true;
		}

		private bool TestCase2()
		{
			print("TestCase2()");

			try {
				number one = 1;
				print("one = " + one);

				throw;

				assert( false );
			}
			finally {
				number one = 2;
				print("one = " + one);
			}

			return true;
		}

		private bool TestCase3()
		{
			print("TestCase3()");

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
*/
			finally {
				number one = 3;
				print("one = " + one);
			}
			return true;
		}

		private bool TestCase4()
		{
			print("TestCase4()");

			number one = 1;
			print("one = " + one);

			throw;

			assert( false );
		}

		private bool TestCase5()
		{
			print("TestCase5()");

			ObjectThatThrows obj = new ObjectThatThrows();

			try {
				print("try");

				obj.MethodThatThrows();

				assert( false );
			}
/*
			catch {
				print("catch");
			}
*/
			finally {
				print("finally");
			}
		}
	}
}

