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
		
		/////////////////////////////////////////////////////////////////////
		
		public bool operator_greater_equal(Number other const) const
		{
			print("operator_greater_equal(Number)");

			if ( mValue >= other ) {
				return true;
			}

			return false;
		}

		public bool operator_greater_equal(UserObject other ref const) const
		{
			print("operator_greater_equal(UserObject)");

			if ( mValue >= other.GetValue() ) {
				return true;
			}

			return false;
		}
	}

	public object Main
	{
		public void Main(Number argc = 0, string argv = "")
		{
			assert(TestCase1());
			assert(TestCase2());
		}

		private bool TestCase1() const
		{
			print("TestCase1: greater-equal operator with atomic type");

			UserObject obj1 = new UserObject(2);

			//assert(obj1 >= 1);
			if ( obj1 >= 1 ) {
				print("obj1 >= 1");
				return true;
			}

			return false;
		}

		private bool TestCase2() const
		{
			print("TestCase2: greater operator with object");

			UserObject obj1 = new UserObject(2);
			UserObject obj2 = new UserObject(1);

			//assert(obj1 >= obj2);
			if ( obj1 >= obj2 ) {
				print("obj1 >= obj2");
				return true;
			}

			return false;
		}
	}
}
