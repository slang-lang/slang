#!/usr/local/bin/oscript

public namespace MathOverloads
{
	private object OverloadedObject
	{
		private Number mNumber;

		public void OverloadedObject(Number one const)
		{
			mNumber = one;
			mNumber = 1;
		}

		public Number GetNumber() const
		{
			return mNumber;
		}

		/////////////////////////////////////////////////////////////////////

		public void operator_divide(Number other const)
		{
			print("operator_divide");
			mNumber = mNumber / other;
		}

		public void operator_multiply(Number other const)
		{
			print("operator_multiply");
			mNumber = mNumber * other;
		}

		public void operator_plus(Number other const)
		{
			print("operator_plus");
			mNumber = mNumber + other;
		}

		public void operator_subtract(Number other const)
		{
			print("operator_subtract");
			mNumber = mNumber - other;
		}
	}

	public object Main
	{
		public void Main(Number argc const = 0, String argv const = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
			assert( TestCase3() );
			assert( TestCase4() );
		}

		private Bool TestCase1()
		{
			print("Starting TestCase1: using the overloaded plus operator");

			OverloadedObject obj1 = new OverloadedObject(1);

			obj1 = obj1 + 2;
			//assert(obj1 == 3);
			print("obj1.GetNumber() = " & obj1.GetNumber());

			return true;
		}

		private Bool TestCase2()
		{
			print("Starting TestCase2: using the overloaded subtract operator");

			OverloadedObject obj1 = new OverloadedObject(1);

			obj1 = obj1 - 2;
			//assert( obj1 == -1 );
			print("obj1.GetNumber() = " & obj1.GetNumber());

			return true;
		}

		private Bool TestCase3()
		{
			print("Starting TestCase3: using the overloaded multiply operator");

			OverloadedObject obj1 = new OverloadedObject(1);

			obj1 = obj1 * 2;
			//assert( obj1 == 2 );
			print("obj1.GetNumber() = " & obj1.GetNumber());

			return true;
		}

		private Bool TestCase4()
		{
			print("Starting TestCase4: using the overloaded divide operator");

			OverloadedObject obj1 = new OverloadedObject(1);

			obj1 = obj1 / 2;
			//assert( obj1 == 0.5 );
			print("obj1.GetNumber() = " & obj1.GetNumber());

			return true;
		}
	}
}
