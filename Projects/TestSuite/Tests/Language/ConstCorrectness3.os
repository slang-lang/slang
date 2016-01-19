#!/usr/local/bin/oscript

public namespace ConstCorrectness
{
	private object UserObject
	{
		private number mValue;

		public void UserObject(number value const)
		{
			mValue = value;
		}

		public void ~UserObject()
		{
		}

		public number getValue() const
		{
			return mValue;
		}

		public void setValue(number value const) modify
		{
			mValue = value;
		}
	}

	public object Main
	{
		private number mNumber;

		public void Main(number argc const = 0, string argv const = "")
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

		private bool UpdateConstUserObject(UserObject objConstRef const ref) const
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
