#!/usr/local/bin/oscript

private namespace BooleanOverloads
{
	private object UserObject
	{
		private Number mValue;

		public void UserObject(Number value const)
		{
			mValue = value;
		}

		public Number GetValue() const
		{
			return mValue;
		}

		public void setValue(Number value const)
		{
			mValue = value;
		}

		/////////////////////////////////////////////////////////////////////

		public void operator_assign(Number other const) modify
		{
			mValue = other;
		}

		public void operator_assign(UserObject other const ref) modify
		{
			mValue = other.GetValue();
		}

		public Bool operator_equal(Number other const) const
		{
			if ( mValue == other ) {
				return true;
			}

			return false;
		}

		public Bool operator_equal(UserObject other const ref) const
		{
			if ( mValue == other.GetValue() ) {
				return true;
			}

			return false;
		}
	}

	public object Main
	{
		public void Main(Number argc = 0, String argv = "")
		{
			assert(TestCase1());
			assert(TestCase2());
		}

		private Bool TestCase1() const
		{
			print("TestCase1: assign operator with atomic type");

			UserObject obj1 = new UserObject(1);

			obj1 = 2;
			//obj1.setValue(2);
			//assert( obj1.GetValue() == 2 );
			if ( obj1 == 2 ) {
				print("obj1 == 2");
				return true;
			}

			return false;
		}

		private Bool TestCase2() const
		{
			print("TestCase2: assign operator with object");

			UserObject obj1 = new UserObject(1);
			UserObject obj2 = new UserObject(1);

			obj1 = obj2;
			//assert( obj1.GetValue() == obj2.GetValue() );
			if ( obj1 == obj2 ) {
				print("obj1 == obj2");
				return true;
			}

			return false;
		}
	}
}
