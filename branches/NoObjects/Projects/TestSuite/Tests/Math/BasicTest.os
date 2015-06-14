#!/usr/bin/oscript

public namespace 
{
	public object Main
	{
		public void Main(Number argc = 0, String argv = "")
		{
			MathExpressionParsing();
		}

		public void MathExpressionParsing()
		{
			Number i = 0;
			assert(i == 0);

			i = 1 + 2 + 3;
			assert(i == 6);

			i = 1 + (2 + 3);
			assert(i == 6);

			i = 1 + 2 * 3;
			assert(i == 7);

			i = 1 * 2 + 3;
			assert(i == 5);

			i = (1 + 2) * 3;
			assert(i == 9);

			i = 1 * (2 + 3);
			assert(i == 5);
		}
	}
}

