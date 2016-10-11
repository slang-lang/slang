#!/usr/local/bin/oscript

		public void Main(int argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
			assert( TestCase3() );
			assert( TestCase4() );
		}

		private bool TestCase1() const
		{
			print("TestCase1: unary ! operator");

			bool value = false;
			print(value);
			print(!value);

			int intVal = 0;
			print(intVal);
			print(!intVal);

			return !value;
		}

		private bool TestCase2() const
		{
			print("TestCase2: infix -- operator");

			int value = 2;
			value = --value;

			return value == 1;
		}

		private bool TestCase3() const
		{
			print("TestCase3: infix ++ operator");

			int value = 2;
			value = ++value;

			return value == 3;
		}

		private bool TestCase4() const
		{
			print("TestCase4: unary - operator");

			int value = 2;
			print("value = " + value);
			value = -1;
			print("value = " + value);

			return value == -1;
		}

