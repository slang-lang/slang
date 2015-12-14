#!/usr/local/bin/oscript

public namespace Tests
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			DefaultParameter();
			DefaultParameter(2);
		}

		private void DefaultParameter(number param = 1)
		{
			print("param = " & param);
		}
	}
}
