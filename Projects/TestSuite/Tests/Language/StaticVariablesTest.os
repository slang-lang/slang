#!/usr/local/bin/oscript

public namespace Language
{
	public object Main
	{
		public void Main(Number argc = 0, string argv = "")
		{
			Number i = 0;

			i = incStaticVar();
			print("i = " & i);

			i = incStaticVar();
			print("i = " & i);

			i = incStaticVar();
			print("i = " & i);
		}

		private Number incStaticVar()
		{
			Number var static = 0;

			var = var + 1;

			return var;
		}
	}
}