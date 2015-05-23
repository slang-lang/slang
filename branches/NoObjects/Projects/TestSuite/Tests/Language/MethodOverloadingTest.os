#!/usr/bin/oscript

public namespace
{
	public object Main
	{
		public void Main()
		{
			returnVoid();

			Number i = 0;
			i = testMethod(returnNumber(1), returnNumber(2));
			print("i = " & i);

			i = returnSum(2, 3);
			print("i = " & i);

			i = returnSum(3, 4, 5);
			print("i = " & i);

			i = returnSum("6+", "7");
			print("i = " & i);

			i = returnSum(""&8, "9");
			print("i = " & i);
		}

		private Number returnNumber(Number param1) const
		{
			return param1;
		}

		private Number returnSum(Number p1, Number p2) const
		{
			return p1 + p2;
		}

		private Number returnSum(Number p1, Number p2, Number p3) const
		{
			return p1 + p2 + p3;
		}

		private String returnSum(String p1, String p2) const
		{
			return p1 & p2;
		}

		private void returnVoid()
		{
			print("method without parameters called which returns nothing");
		}

		private Number testMethod(Number param1, Number param2) const
		{
			return param1 + param2;
		}
	}
}
