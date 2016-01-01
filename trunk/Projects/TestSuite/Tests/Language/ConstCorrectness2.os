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
			mNumber = 0;

			assert( UpdateMember(1) );
			//assert( UpdateConstMember(2) );

			assert( ObjectAsReference() );
			assert( ObjectAsConstReference() );
		}

		private bool UpdateConstMember(number value const) const
		{
			// if we reach the end of our method without a ConstCorrectnessViolated exception being raise, something is very wrong

			mNumber = value;

			return false;
		}

		private bool UpdateMember(number value const) modify
		{
			// this method should be executed successfully

			mNumber = value;

			return true;
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

			return true;
		}

		private bool UpdateConstUserObject(UserObject obj const ref) const
		{
			// altough all objects are references it should never be possible to change a const object => fail

			obj.setValue(2);

			return false;
		}

		private bool UpdateUserObject(UserObject obj ref) const
		{
			// all objects are references so this is perfectly valid => success

			obj.setValue(2);

			return true;
		}
	}
}
