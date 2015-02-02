
import system.assert;

public namespace
{
	private object Main
	{
		public void Main()
		{
		}

		public void ~Main()
		{
		}

		public void test_assert()
		{
			assert(true);
			assert(incStaticVar());
			assert(incStaticVar() & "bla");
			assert(true == false);
		}

		public void test_comments(/*number param1*/)
		{
			//this is a single line comment
			// this is another single line comment
			/*this is a multi
				line comment*/
			/* this is another multi
				line comment */
			/*
			print("this will not be executed");
			*/
			print("this is /* not */ a comment");
		}

		public void test_executeMethod()
		{
			returnVoid();

			Number i = 0;
			i = testMethod(
				returnNumber(1),
				returnNumber(2)
			);
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

		public void test_for()
		{
			breakpoint;

			for ( Number i = 0; i < 5; i = i + 1; ) {
				print("i = " & i);
			}

			breakpoint;
		}

		public void test_if(Number param1)
		{
			if ( false ) {
				print("if: false");
			}
			else {
				print("if: else");
			}

			if ( true ) {
				print("if: true");
			}

			if ( param1 - 1 == 0 ) {
				print("if: true");
			}
			else if ( true ) {
				print("else if: true");
			}
			else {
				print("else if: else");
			}
		}

		public void test_print(String param1)
		{
			print("print 'text' with single quotes");
			print("print \"text\" with double quotes");
			print("print text with numbers 1234567890");
			print("print text with special characters: ,.-;:_#'+*�`�?");
			print(1 + 2);
			print(1 & param1 & 2);
		}

		public void test_static_local_variable()
		{
			Number i = 0;

			i = incStaticVar();
			print("i = " & i);

			i = incStaticVar();
			print("i = " & i);

			i = incStaticVar();
			print("i = " & i);
		}

		public void test_while(Number maxCount)
		{
			breakpoint;

			Number count = 0;
			while ( count < maxCount ) {
				count = count + 1;
				print("count = " & count);
			}

			breakpoint;
		}

	/////////////////////////////////// Private Methods \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

		private Number incStaticVar()
		{
			Number var static = 0;

			var = var + 1;

			return var;
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
