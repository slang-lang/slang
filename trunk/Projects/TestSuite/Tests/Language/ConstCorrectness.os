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
			//ModifyByReferenceParameter(one);	// this is not supported atm

			number two const = 0;
			ModifyConstParameter(two);

			number three = 0;
			ModifyMemberInConstMethod(three);
		}

		private void ModifyByReferenceParameter(number value ref) modify
		{
			mNumber = 1;
			value = 1;
		}

		private void ModifyByValueParameter(number value val) modify
		{
			mNumber = 1;
			value = 1;
		}

		private void ModifyConstParameter(number value const) modify
		{
			mNumber = 2;	// allowed
			value = 2;		// throws a ConstCorrectnessViolated exception
		}

		private void ModifyMemberInConstMethod(number value const) const
		{
			mNumber = value;	// throws a ConstCorrectnessViolated exception
		}
	}
}
