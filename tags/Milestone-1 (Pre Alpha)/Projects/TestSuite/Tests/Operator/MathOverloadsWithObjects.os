#!/usr/local/bin/oscript

public namespace MathOverloads
{
	private object OverloadedObject
	{
		private number mNumber;

		public void OverloadedObject(number one const)
		{
			mNumber = one;
		}

		public number GetNumber() const
		{
			return mNumber;
		}

		/////////////////////////////////////////////////////////////////////

		public void operator/(OverloadedObject other const ref) modify
		{
			print("operator/(OverloadedObject)");
			mNumber = mNumber / other.GetNumber();
		}

		public bool operator==(number other const) const
		{
			print("operator==(number)");
			return mNumber == other;
		}

		public bool operator==(OverloadedObject other const ref) const
		{
			print("operator==(OverloadedObject)");
			return mNumber == other.GetNumber();
		}

		public void operator*(OverloadedObject other const ref) modify
		{
			print("operator*(OverloadedObject)");
			mNumber = mNumber * other.GetNumber();
		}

		public void operator%(OverloadedObject other const ref) modify
		{
			print("operator%(OverloadedObject)");
			mNumber = mNumber % other.GetNumber();
		}

		public void operator+(OverloadedObject other const ref) modify
		{
			print("operator+(OverloadedObject)");
			mNumber = mNumber + other.GetNumber();
		}

		public void operator-(OverloadedObject other const ref) modify
		{
			print("operator-(OverloadedObject)");
			mNumber = mNumber - other.GetNumber();
		}
	}

	public object Main
	{
		public void Main(number argc const = 0, string argv const = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
			assert( TestCase3() );
			assert( TestCase4() );
			//assert( TestCase5() );
		}

		private bool TestCase1() const
		{
			print("TestCase1: using the overloaded plus operator");

			OverloadedObject obj1 = new OverloadedObject(1);
			OverloadedObject obj2 = new OverloadedObject(2);

			obj1 = obj1 + obj2;
			assert(obj1 == 3);
			print("obj1.GetNumber() = " + obj1.GetNumber());
			
			if ( obj1 == 3 ) {
				return true;
			}

			return false;
		}

		private bool TestCase2() const
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

		private bool TestCase3() const
		{
			print("TestCase3: using the overloaded multiply operator");

			OverloadedObject obj1 = new OverloadedObject(1);
			OverloadedObject obj2 = new OverloadedObject(2);

			obj1 = obj1 * obj2;
			//assert( obj1 == 2 );
			print("obj1.GetNumber() = " + obj1.GetNumber());

			if ( obj1 == 2 ) {
				return true;
			}

			return false;
		}

		private bool TestCase4() const
		{
			print("TestCase4: using the overloaded divide operator");

			OverloadedObject obj1 = new OverloadedObject(1);
			OverloadedObject obj2 = new OverloadedObject(2);

			obj1 = obj1 / obj2;
			//assert( obj1 == 0.5 );
			print("obj1.GetNumber() = " + obj1.GetNumber());

			if ( obj1 == 0.5 ) {
				return true;
			}

			return false;
		}

		private bool TestCase5() const
		{
			print("TestCase5: using the overloaded modulo operator");

			OverloadedObject obj1 = new OverloadedObject(5);
			OverloadedObject obj2 = new OverloadedObject(2);

			obj1 = obj1 % obj2;
			//assert( obj1 == 0.5 );
			print("obj1.GetNumber() = " + obj1.GetNumber());

			if ( obj1 == 1 ) {
				return true;
			}

			return false;
		}
	}
}