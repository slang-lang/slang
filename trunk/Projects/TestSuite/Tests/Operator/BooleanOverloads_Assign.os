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

		public int getValue() const
		{
			return mValue;
		}

		public void setValue(int value const)
		{
			mValue = value;
		}

		/////////////////////////////////////////////////////////////////////

		public void operator=(int other const) modify
		{
			mValue = other;
		}

		public void operator=(UserObject other const) modify
		{
			mValue = other.getValue();
		}

		public bool operator==(int other const) const
		{
			return mValue == other;
		}

		public bool operator==(UserObject other const) const
		{
			return mValue == other.getValue();
		}

		public string ToString() const
		{
			return (string mValue);
		}
	}
}

	public object Main
	{
		public void Main(int argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
		}

		private bool TestCase1() const
		{
			print("TestCase1: assign operator with atomic type");

			BooleanOverloads.UserObject obj1 = new BooleanOverloads.UserObject(1);

			obj1 = 2;
			assert( obj1 == 2 );
			if ( obj1 == 2 ) {
				print("obj1 == 2");
				print(obj1.ToString() + " == 2");
				return true;
			}

			return false;
		}

		private bool TestCase2() const
		{
			print("TestCase2: assign operator with object");

			BooleanOverloads.UserObject obj1 = new BooleanOverloads.UserObject(1);
			BooleanOverloads.UserObject obj2 = new BooleanOverloads.UserObject(1);

			obj1 = obj2;
			assert( obj1 == obj2 );
			if ( obj1 == obj2 ) {
				print("obj1 == obj2");
				print(obj1.ToString() + " == " + obj2.ToString());
				return true;
			}

			return false;
		}
	}
