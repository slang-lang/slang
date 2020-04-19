#!/usr/local/bin/slang

public void Main(int argc = 0, string argv = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

private bool TestCase1() const {
	print("TestCase 1: postfix -- operator");

	int value = 2;
	print("value = " + value);
	value = value--;
	print("value = " + value);

	return value == 1;
}

private bool TestCase2() const {
	print("TestCase 2: postfix ++ operator");

	int value = 2;
	print("value = " + value);
	value = value++;
	print("value = " + value);

	return value == 3;
}

private bool TestCase3() const {
	print("TestCase 3: postfix ++ operator");

	int value = 2;
	print("value = " + value);

	print(value++);

	int i = value++ + 1;
	print("i = " + i);

	return i == 5;
}

