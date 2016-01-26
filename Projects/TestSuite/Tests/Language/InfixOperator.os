#!/usr/local/bin/oscript

public namespace InfixOperator
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
			//assert( TestCase2() );
			//assert( TestCase3() );
			assert( TestCase4() );
		}

		private bool TestCase1() const
		{
			print("TestCase1: unary ! operator");

			bool value = false;

			return !value;
		}

		private bool TestCase2() const
		{
			print("TestCase2: infix -- operator");

			number value = 2;
			--value;

			return value == 1;
		}

		private bool TestCase3() const
		{
			print("TestCase3: infix ++ operator");

			number value = 2;
			++value;

			return value == 3;
		}

		private bool TestCase4() const
		{
			print("TestCase4: unary - operator");

			number value = 2;
			print("value = " + value);
			value = -1;
			print("value = " + value);

			return value == -1;
		}
	}
}
