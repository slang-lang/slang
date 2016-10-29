#!/usr/local/bin/oscript

import System.Boolean;

		public void Main(int argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
			assert( TestCase3() );
			assert( TestCase4() );
			assert( TestCase5() );
			assert( TestCase6() );
			//assert( TestCase7() );
		}

		private bool TestCase1() const
		{
			print("TestCase 1: int to bool type cast");
			
			int value = 5;
			bool state = false;

			state = (bool value);
			print("(bool value) = " + (bool value));
			print("state = " + state);

			return state;
		}

		private bool TestCase2() const
		{
			print("TestCase 2: int to int type cast");

			int integral = 2;
			print("integral = " + int integral);

			int value = 3 + (int integral);
			print("value = " + value);

			return true;
		}

		private bool TestCase3() const
		{
			print("TestCase 3: float to int type cast");

			float real = 3.5f;
			print("float = " + int real);

			int value = 3 + (int real);
			print("value = " + value);

			return true;
		}

		private bool TestCase4() const
		{
			print("TestCase 4: float to int type cast");

			float real = 3.5f;
			print("float = " + int real);

			int value = 3 + int real;
			print("value = " + value);

			return true;
		}

		private bool TestCase5() const
		{
			print("TestCase 5: string to int type cast");

			string str = "3.5f";
			print("string = " + int str);

			int value = 3 + (int str);
			print("value = " + value);

			return true;
		}

		private bool TestCase6() const
		{
			print("TestCase 6: invalid string to int type cast");

			string str = "bla";
			print("string = " + int str);

			return true;
		}

		private bool TestCase7() const
		{
			print("TestCase 7: value to object type cast");

			Boolean boolVal = new Boolean(true);
			int intVal = 17;

			print(Boolean intVal);

			return true;
		}

