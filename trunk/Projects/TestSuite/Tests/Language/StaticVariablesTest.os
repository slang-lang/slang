#!/usr/local/bin/oscript

public namespace Language
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
		}

		private bool TestCase1()
		{
			number i = 0;

			i = incStaticVar();
			print("i = " + i);

			i = incStaticVar();
			print("i = " + i);

			i = incStaticVar();
			print("i = " + i);

			return i == 3;
		}

		private number incStaticVar()
		{
			number var static = 0;

			var = var + 1;

			return var;
		}
	}
}
