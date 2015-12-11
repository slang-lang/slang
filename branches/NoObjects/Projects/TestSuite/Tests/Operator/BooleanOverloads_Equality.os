
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
		
		public Bool operator_equal(Number other const)
		{
			if ( mValue == other ) {
				return true;
			}
			
			return false;
		}
		
		public Bool operator_equal(UserObject other const)
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

		private Bool TestCase1()
		{
			print("TestCase1: equality operator with atomic type");
			
			UserObject obj1 = new UserObject(1);
			
			//assert(obj1 == 1);
			if ( obj1 == 1 ) {
				print("obj1 == 1: 1");
				return true;
			}

			return false;
		}

		private Bool TestCase2()
		{
			print("TestCase2: equality operator with object");
			
			UserObject obj1 = new UserObject(1);
			UserObject obj2 = new UserObject(1);
			
			//assert(obj1 == obj2);
			if ( obj1 == obj2 ) {
				print("obj1 == obj2: 1");
				return true;
			}

			return false;
		}
	}
}
