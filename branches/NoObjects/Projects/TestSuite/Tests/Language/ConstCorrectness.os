#!/usr/bin/oscript

public namespace ConstCorrectness
{
	public object Main
	{
		private Number mNumber;

		public void Main(Number argc const = 0, String argv const = "")
		{
			mNumber = 0;

			Number one = 1;
			ModifyByValueParameter(one);

			one = 0;
			//ModifyByReferenceParameter(one);

			Number two const = 0;
			ModifyConstParameter(two);

			Number three = 0;
			ModifyMemberInConstMethod(three);
		}

		private void ModifyByValueParameter(Number one val) modify
		{
			mNumber = 1;
			one = 1;
		}

		private void ModifyByReferenceParameter(Number one ref) modify
		{
			mNumber = 1;
			one = 1;
		}

		private void ModifyConstParameter(Number two const) modify
		{
			mNumber = 2;
			two = 2;
		}

		private void ModifyMemberInConstMethod(Number three) const
		{
			mNumber = 3;
			three = 3;
		}
	}
}
