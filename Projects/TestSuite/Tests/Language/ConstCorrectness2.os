#!/usr/local/bin/oscript

public namespace ConstCorrectness
{
	private object UserObject
	{
		private Number mValue;

		public void UserObject(Number value const)
		{
			mValue = value;
		}

		public Number getValue() const
		{
			return mValue;
		}

		public void setValue(Number value const)
		{
			mValue = value;
		}
	}

	public object Main
	{
		public void Main(Number argc const = 0, String argv const = "")
		{
			//assert( ObjectAsReference() );
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
