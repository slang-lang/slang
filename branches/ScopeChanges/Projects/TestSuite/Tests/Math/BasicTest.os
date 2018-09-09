#!/usr/local/bin/oscript

public void Main(int argc = 0, string argv = "") {
	 MathExpressionParsing();
}

public void MathExpressionParsing() {
	int i = 0;
	print("i == 0: " + i);
	assert(i == 0);

	i = 1 + 2 + 3;
	print("i == 6: " + i);
	assert(i == 6);

	i = 1 + (2 + 3);
	print("i == 6: " + i);
	assert(i == 6);

	i = 1 + 2 * 3;
	print("i == 7: " + i);
	assert(i == 7);

	i = 1 * 2 + 3;
	print("i == 5: " + i);
	assert(i == 5);

	i = (1 + 2) * 3;
	print("i == 9: " + i);
	assert(i == 9);

	i = 1 * (2 + 3);
	print("i == 5: " + i);
	assert(i == 5);
}

