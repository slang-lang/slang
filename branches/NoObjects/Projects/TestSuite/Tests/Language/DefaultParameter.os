
public namespace Tests
{
	public object Main
	{
		public void Main()
		{
			DefaultParameter();
			DefaultParameter(2);
		}

		private void DefaultParameter(Number param = 1)
		{
			print("param = " & param);
		}
	}
}
