#!/usr/local/bin/oscript

public namespace Tests
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			print("argc = " + argc);
			print("argv = " + argv);

			print("DefaultParameter();");
			DefaultParameter();
			print("DefaultParameter(2);");
			DefaultParameter(2);
		}

		private void DefaultParameter(number param = 1)
		{
			print("param = " + param);
		}
	}
}
