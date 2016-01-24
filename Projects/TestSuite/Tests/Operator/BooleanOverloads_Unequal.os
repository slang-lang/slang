#!/usr/local/bin/oscript

private namespace BooleanOverloads
{
	private object UserObject
	{
		private number mValue;

		public void UserObject(number value const)
		{
			mValue = value;
		}

		public number GetValue() const
		{
			return mValue;
		}

		/////////////////////////////////////////////////////////////////////

		public bool operator_equal(number other const) const
		{
			print("operator==(number)");

			return mValue == other;
		}

		public bool operator_equal(UserObject other const) const
		{
			print("operator==(UserObject)");

			return mValue == other.GetValue();
		}
	}

	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert(TestCase1());
			assert(TestCase2());
		}

		private bool TestCase1() const
		{
			print("TestCase1: unequal operator with atomic type");

			UserObject obj1 = new UserObject(1);

			//assert(obj1 != 2);
			if ( obj1 != 2 ) {
				print("obj1 != 2");
				return true;
			}

			return false;
		}

		private bool TestCase2() const
		{
			print("TestCase2: unequal operator with object");

			UserObject obj1 = new UserObject(1);
			UserObject obj2 = new UserObject(2);

			//assert(obj1 != obj2);
			if ( obj1 != obj2 ) {
				print("obj1 != obj2");
				return true;
			}

			return false;
		}
	}
}
