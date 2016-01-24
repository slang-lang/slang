#!/usr/local/bin/oscript

public namespace InfixOperator
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
			print("TestCase1: postfix -- operator");

			number value = 2;
			print("value = " + value);
			value--;
			print("value = " + value);

			return value == 1;
		}

		private bool TestCase2() const
		{
			print("TestCase2: postfix ++ operator");

			number value = 2;
			print("value = " + value);
			value++;
			print("value = " + value);

			return value == 3;
		}
	}
}
