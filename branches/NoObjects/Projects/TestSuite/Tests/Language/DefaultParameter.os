#!/usr/bin/oscript

public namespace Tests
{
	public object Main
	{
		public void Main(Number argc = 0, String argv = "")
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
