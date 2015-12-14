#!/usr/local/bin/oscript

public namespace BasicTest
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			MathExpressionParsing();
		}

		public void MathExpressionParsing()
		{
			number i = 0;
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

