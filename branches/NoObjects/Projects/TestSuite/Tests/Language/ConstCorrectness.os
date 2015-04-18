
public namespace
{
	public object Main
	{
		private Number mNumber;

		public void Main()
		{
			mNumber = 1;
		}

		public void ModifyConstParameter(Number two const)
		{
			two = 2;
		}

		public void ModifyMemberInConstMethod() const
		{
			mNumber = 3;
		}
	}
}

