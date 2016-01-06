#!/usr/local/bin/oscript

public namespace 
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			returnVoid();

			number i = 0;
			i = testMethod(returnNumber(1), returnNumber(2));
			print("i = " + i);

			i = returnSum(2, 3);
			print("i = " + i);

			i = returnSum(3, 4, 5);
			print("i = " + i);

			i = returnSum("6+", "7");
			print("i = " + i);

			i = returnSum("" + 8, "9");
			print("i = " + i);
		}

		private number returnNumber(number param1) const
		{
			return param1;
		}

		private number returnSum(number p1, number p2) const
		{
			return p1 + p2;
		}

		private number returnSum(number p1, number p2, number p3) const
		{
			return p1 + p2 + p3;
		}

		private string returnSum(string p1, string p2) const
		{
			return "" + p1 + p2;
		}

		private void returnVoid()
		{
			print("method without parameters called which returns nothing");
			return;
		}

		private number testMethod(number param1, number param2) const
		{
			return param1 + param2;
		}
	}
}
