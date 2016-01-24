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
		}

		private bool TestCase1() const
		{
			bool value = false;

			return !value;
		}

		private bool TestCase2() const
		{
			number value = 2;
			--value;

			return value == 1;
		}

		private bool TestCase3() const
		{
			number value = 2;
			++value;

			return value == 3;
		}
	}
}
