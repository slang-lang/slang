#!/usr/local/bin/oscript

public object Main {
	public void Main(int argc = 0, string argv = "") {
		assert( TestCase1() );
	}

	private bool TestCase1() const {
		test_print(" parameter ");

		return true;
	}

	public void test_print(string param1) {
		print("print 'text' with single quotes");
		print("print \"text\" with double quotes");
		print("print text with numbers 1234567890");
		print("print text with special characters: ,.-;:_#'+*?`??");
		print("print text with\t\ttabs");
		print(1 + 2);
		print((string 1) + param1 + (string 2));
	}
}

