#!/usr/bin/oscript

public namespace
{
	public object Main
	{
		private Number mNumber;

		public void Main(Number argc = 0, String argv = "")
		{
			mNumber = 1;

			Number two const = 0;
			ModifyConstParameter(two);

			Number three = 0;
			ModifyMemberInConstMethod(three);
		}

		public void ModifyConstParameter(Number two const)
		{
			mNumber = 2;
			two = 2;
		}

		public void ModifyMemberInConstMethod(Number three) const
		{
			mNumber = 3;
			three = 3;
		}
	}
}

