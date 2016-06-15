#!/usr/local/bin/oscript

public namespace ConstCorrectness2
{
	public object Main
	{
		private int mNumber;

		public void Main(int argc const = 0, string argv const = "")
		{
			mNumber = 0;

			assert( UpdateMember(1) );
			assert( UpdateMemberInConstMethod(2) );
		}

		private bool UpdateMemberInConstMethod(int value const) const
		{
			// if we reach the end of our method without a ConstCorrectnessViolated exception being raise, something is very wrong

			mNumber = value;

			return false;
		}

		private bool UpdateMember(int value const) modify
		{
			// this method should be executed successfully

			mNumber = value;

			return true;
		}
	}
}
