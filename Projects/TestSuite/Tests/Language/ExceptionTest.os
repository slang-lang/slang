#!/usr/local/bin/oscript

public namespace ExceptionTest
{
	private object ObjectThatThrows
	{
/*
		public void ObjectThatThrows()
		{
			// not implementing this constructor and using the default constructor would also be valid
		}
*/
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
			assert( TestCase4() );	// this is not supported as long as we don't define methods in object scope
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
			catch {
				number one = 2;
				print("one = " + one);
			}
			finally {
				number one = 3;
				print("one = " + one);
			}
			return true;
		}

		private bool TestCase4()
		{
			print("TestCase4()");

			ObjectThatThrows obj = new ObjectThatThrows();

			try {
				print("try");

				obj.MethodThatThrows();

				assert( false );
			}
			catch {
				print("catch");
			}
			finally {
				print("finally");
			}
		}

		private bool TestCase5()
		{
			print("TestCase5()");

			number one = 1;
			print("one = " + one);

			try {
				print("outter try");

				try {
					print("inner try");

					throw;

					assert( false );
				}
			}
			finally {
				print("outter finally");
			}
		}
	}
}

