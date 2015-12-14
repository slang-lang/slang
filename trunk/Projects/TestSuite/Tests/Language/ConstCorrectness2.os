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

		public void setValue(number value const)
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
			assert( UpdateConstMember(2) );

			//assert( ObjectAsReference() );
		}

		private bool UpdateConstMember(number value const) const
		{
			mNumber = value;

			return false;
		}

		private bool ObjectAsReference() const
		{
			UserObject obj1 = new UserObject(1);

			UpdateUserObject(obj1);

			return true;
		}

		private bool UpdateUserObject(UserObject obj const) const
		{
			obj.setValue(2);
		}
	}
}
