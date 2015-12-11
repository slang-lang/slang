#!/usr/bin/oscript

public namespace OperatorOverloading
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

		public void operator_assign(Number other const)
		{
			print("operator_assign");
			assert(false);
			mNumber = other;
		}
		public void operator_divide(Number other const)
		{
			print("operator_divide");
			mNumber = mNumber / other;
		}
		public Bool operator_equal(Number other const)
		{
			assert(false);
			return (mNumber == other);
		}
		public Bool operator_greater(Number other const)
		{
			assert(false);
			return (mNumber > other);
		}
		public Bool operator_greater_equal(Number other const)
		{
			assert(false);
			return (mNumber >= other);
		}
		public Bool operator_less(Number other const)
		{
			assert(false);
			return (mNumber < other);
		}
		public Bool operator_less(OverloadedObject other const)
		{
			//return (mNumber < other.GetNumber());
			if ( mNumber < other.GetNumber() ) {
				return true;
			}
			
			return false;
		}
		public Bool operator_less_equal(Number other const)
		{
			assert(false);
			return (mNumber <= other);
		}
		public Bool operator_less_equal(OverloadedObject other const)
		{
			assert(false);
			return (mNumber <= other.GetNumber());
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
			OverloadedObject obj1 = new OverloadedObject(1);
			obj1 = obj1 + 3;
			obj1 = obj1 - 1;
			obj1 = obj1 * 2;
			obj1 = obj1 / 3;

			print("obj1.mNumber = " & obj1.mNumber);
			print("obj1.GetNumber() = " & obj1.GetNumber());

			OverloadedObject obj2 = new OverloadedObject(20);

			//assert( obj1 == 1 );
			if ( obj1 == 1 ) {
				print("obj1 == 1");
			}

			//assert( obj1 < obj2 );
			//assert( obj1 < 20 );
			if ( obj1 < obj2 ) {
				print(obj1 + " is smaller than " + obj2);
			}
			if ( obj1 < obj2 ) {
				print(obj1 + " is smaller than " + obj2);
			}

			//assert( obj1 <= obj );
			if ( obj1 <= obj2 ) {
				print(obj1 + " is smaller than or equal to " + obj2);
			}
		}
	}
}
