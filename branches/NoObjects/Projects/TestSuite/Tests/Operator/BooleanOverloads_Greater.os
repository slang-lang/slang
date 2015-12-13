
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
		
		public Bool operator_greater(Number other const)
		{
			print("operator_greater(Number)");

			if ( mValue > other ) {
				return true;
			}
			
			return false;
		}
		
		public Bool operator_greater(UserObject other ref const)
		{
			print("operator_greater(UserObject)");

			if ( mValue > other.GetValue() ) {
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

		private Bool TestCase1()
		{
			print("TestCase1: greater operator with atomic type");

			UserObject obj1 = new UserObject(2);

			//assert(obj1 > 1);
			if ( obj1 > 1 ) {
				print("obj1 > 1");
				return true;
			}

			return false;
		}

		private Bool TestCase2()
		{
			print("TestCase2: greater operator with object");

			UserObject obj1 = new UserObject(1);
			UserObject obj2 = new UserObject(2);

			//assert(obj2 > obj1);
			if ( obj2 > obj1 ) {
				print("obj2 > obj1");
				return true;
			}

			return false;
		}
	}
}
