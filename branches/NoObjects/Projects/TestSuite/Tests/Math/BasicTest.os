
public namespace Math
{
	public object Main
	{
		public void MathExpressionParsing()
		{
			Number i;
/*
			i = 1 + 2 + 3;
			assert(i == 6);

			i = 1 + (2 + 3);
			assert(i == 6);
*/
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
