#!/usr/local/bin/oscript

public namespace Language
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			test_print(" parameter ");
		}

		public void test_print(string param1)
		{
			print("print 'text' with single quotes");
			print("print \"text\" with double quotes");
			print("print text with numbers 1234567890");
			print("print text with special characters: ,.-;:_#'+*?`??");
			print("print text with\t\ttabs");
			print(1 + 2);
			print(1 + param1 + 2);
		}
	}
}