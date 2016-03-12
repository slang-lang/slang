#!/usr/local/bin/oscript

public namespace ConstCorrectness3
{
	private object UserObject
	{
		private int mValue;

		public void UserObject(int value const)
		{
			mValue = value;
		}

		public void ~UserObject()
		{
		}

		public int getValue() const
		{
			return mValue;
		}

		public void setValue(int value const) modify
		{
			mValue = value;
		}
	}

	public object Main
	{
		private int mNumber;

		public void Main(int argc const = 0, string argv const = "")
		{
			mNumber = 1;

			assert( ObjectAsReference() );
			assert( ObjectAsConstReference() );
		}

		private bool ObjectAsConstReference() const
		{
			// altough all objects are references it should never be possible to change a const object => fail

			UserObject obj1 = new UserObject(1);

			UpdateConstUserObject(obj1);

			return false;
		}

		private bool ObjectAsReference() const
		{
			// all objects are references so this is perfectly valid => success

			UserObject obj1 = new UserObject(1);

			UpdateUserObject(obj1);

			assert( obj1.getValue() == 2 );

			obj1.setValue(3);

			return true;
		}

		private bool UpdateConstUserObject(UserObject objConstRef const) const
		{
			// altough all objects are references it should never be possible to change a const object => fail
			objConstRef.setValue(2);

			return false;
		}

		private bool UpdateUserObject(UserObject objRef ref) const
		{
			// all objects are references so this is perfectly valid => success

			objRef.setValue(2);

			return true;
		}
	}
}
