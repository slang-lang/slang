#!/usr/local/bin/oscript

public namespace TypeCastTest
{
	public object Main
	{
private void Bla() abstract

		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
			assert( TestCase3() );
			assert( TestCase4() );
			assert( TestCase5() );
		}

		private bool TestCase1() const
		{
			print("TestCase 1: number to bool type cast");
			
			number value = 5;
			bool state = false;

			state = (bool value);
			print("(bool value) = " + (bool value));
			print("state = " + state);

			return state;
		}

		private bool TestCase2() const
		{
			print("TestCase 2: int to number type cast");
			int integral = 2i;
			print("integral = " + number integral);

			number value = 3 + (number integral);
			print("value = " + value);

			return true;
		}

		private bool TestCase3() const
		{
			print("TestCase 3: float to int type cast");
			float real = 3.5f;
			print("float = " + number real);

			int value = 3 + (int real);
			print("value = " + value);

			return true;
		}

		private bool TestCase4() const
		{
			print("TestCase 4: float to number type cast");
			float real = 3.5f;
			print("float = " + number real);

			number value = 3 + (number real);
			print("value = " + value);

			return true;
		}

		private bool TestCase5() const
		{
			print("TestCase 5: string to number type cast");
			string str = "3.5f";
			print("string = " + number str);

			number value = 3 + (number str);
			print("value = " + value);

			return true;
		}
	}
}
