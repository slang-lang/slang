#!/usr/local/bin/oscript

public namespace MathOverloads
{
	private object OverloadedObject
	{
		private Number mNumber;

		public void OverloadedObject(Number one const)
		{
			mNumber = one;
		}

		public Number GetNumber() const
		{
			return mNumber;
		}

		/////////////////////////////////////////////////////////////////////

		public void operator_divide(OverloadedObject other ref const)
		{
			print("operator_divide(OverloadedObject)");
			mNumber = mNumber / other.GetNumber();
		}

		public void operator_equal(OverloadedObject other const)
		{
			print("operator_equal(OverloadedObject)");
			
			if ( mNumber == other.GetNumber() ) {
				return true;
			}
			
			return false;
		}
		
		public void operator_equal(Number other const)
		{
			print("operator_equal(Number)");
			
			if ( mNumber == other ) {
				return true;
			}
			
			return false;
		}

		public void operator_multiply(OverloadedObject other ref const)
		{
			print("operator_multiply(OverloadedObject)");
			mNumber = mNumber * other.GetNumber();
		}

		public void operator_plus(OverloadedObject other ref const)
		{
			print("operator_plus(OverloadedObject)");
			mNumber = mNumber + other.GetNumber();
		}

		public void operator_subtract(OverloadedObject other ref const)
		{
			print("operator_subtract(OverloadedObject)");
			mNumber = mNumber - other.GetNumber();
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
			print("TestCase1: using the overloaded plus operator");

			OverloadedObject obj1 = new OverloadedObject(1);
			OverloadedObject obj2 = new OverloadedObject(2);

			obj1 = obj1 + obj2;
			//assert(obj1 == 3);
			print("obj1.GetNumber() = " & obj1.GetNumber());
			
			if ( obj1 == 3 ) {
				return true;
			}

			return false;
		}

		private Bool TestCase2()
		{
			print("TestCase2: using the overloaded subtract operator");

			OverloadedObject obj1 = new OverloadedObject(1);
			OverloadedObject obj2 = new OverloadedObject(2);

			obj1 = obj1 - obj2;
			//assert( obj1 == -1 );
			print("obj1.GetNumber() = " + obj1.GetNumber());

			if ( obj1 == obj1.GetNumber() ) {
				return true;
			}

			return false;
		}

		private Bool TestCase3()
		{
			print("TestCase3: using the overloaded multiply operator");

			OverloadedObject obj1 = new OverloadedObject(1);
			OverloadedObject obj2 = new OverloadedObject(2);

			obj1 = obj1 * obj2;
			//assert( obj1 == 2 );
			print("obj1.GetNumber() = " & obj1.GetNumber());

			if ( obj1 == 2 ) {
				return true;
			}

			return false;
		}

		private Bool TestCase4()
		{
			print("TestCase4: using the overloaded divide operator");

			OverloadedObject obj1 = new OverloadedObject(1);
			OverloadedObject obj2 = new OverloadedObject(2);

			obj1 = obj1 / obj2;
			//assert( obj1 == 0.5 );
			print("obj1.GetNumber() = " & obj1.GetNumber());

			if ( obj1 == 0.5 ) {
				return true;
			}

			return false;
		}
	}
}
