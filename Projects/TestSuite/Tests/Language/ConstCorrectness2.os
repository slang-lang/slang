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
			assert( UpdateConstMember(2) );
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
	}
}
