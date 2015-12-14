#!/usr/local/bin/oscript

public namespace ConstCorrectness
{
	public object Main
	{
		private number mNumber;

		public void Main(number argc const = 0, string argv const = "")
		{
			mNumber = 0;

			number one = 1;
			ModifyByValueParameter(one);

			one = 0;
			//ModifyByReferenceParameter(one);

			number two const = 0;
			ModifyConstParameter(two);

			number three = 0;
			ModifyMemberInConstMethod(three);
		}

		private void ModifyByValueParameter(number one val) modify
		{
			mNumber = 1;
			one = 1;
		}

		private void ModifyByReferenceParameter(number one ref) modify
		{
			mNumber = 1;
			one = 1;
		}

		private void ModifyConstParameter(number two const) modify
		{
			mNumber = 2;
			two = 2;
		}

		private void ModifyMemberInConstMethod(number three) const
		{
			mNumber = 3;
			three = 3;
		}
	}
}
