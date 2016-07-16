#!/usr/local/bin/oscript

private namespace BooleanOverloads
{
	private object UserObject
	{
		private int mValue;

		public void UserObject(int value const)
		{
			mValue = value;
		}

		public int GetValue() const
		{
			return mValue;
		}
		
		/////////////////////////////////////////////////////////////////////
		
		public bool operator>=(int other const) const
		{
			print("operator>=(int)");
			return mValue >= other;
		}

		public bool operator>=(UserObject other const) const
		{
			print("operator>=(UserObject)");
			return mValue >= other.GetValue();
		}
	}
}

	public object Main
	{
		public void Main(int argc = 0, string argv = "")
		{
			assert(TestCase1());
			assert(TestCase2());
		}

		private bool TestCase1() const
		{
			print("TestCase1: greater-equal operator with atomic type");

			BooleanOverloads.UserObject obj1 = new BooleanOverloads.UserObject(2);

			assert(obj1 >= 1);
			if ( obj1 >= 1 ) {
				print("obj1 >= 1");
				return true;
			}

			return false;
		}

		private bool TestCase2() const
		{
			print("TestCase2: greater operator with object");

			BooleanOverloads.UserObject obj1 = new BooleanOverloads.UserObject(2);
			BooleanOverloads.UserObject obj2 = new BooleanOverloads.UserObject(1);

			assert(obj1 >= obj2);
			if ( obj1 >= obj2 ) {
				print("obj1 >= obj2");
				return true;
			}

			return false;
		}
	}

