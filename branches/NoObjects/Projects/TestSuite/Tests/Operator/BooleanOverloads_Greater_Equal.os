
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
		
		public Bool operator_greater_equal(Number other const) const
		{
			print("operator_greater_equal(Number)");

			if ( mValue >= other ) {
				return true;
			}

			return false;
		}

		public Bool operator_greater_equal(UserObject other ref const) const
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
		public void Main(Number argc = 0, String argv = "")
		{
			assert(TestCase1());
			assert(TestCase2());
		}

		private Bool TestCase1() const
		{
			print("TestCase1: greater-equal operator with atomic type");

			UserObject obj1 = new UserObject(1);

			//assert(obj1 >= 2);
			if ( obj1 >= 2 ) {
				print("obj1 >= 2");
				return true;
			}

			return false;
		}

		private Bool TestCase2() const
		{
			print("TestCase2: greater operator with object");

			UserObject obj1 = new UserObject(1);
			UserObject obj2 = new UserObject(2);

			//assert(obj1 >= obj2);
			if ( obj1 >= obj2 ) {
				print("obj1 >= obj2");
				return true;
			}

			return false;
		}
	}
}
