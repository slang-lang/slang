#!/usr/local/bin/slang

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
}

public bool TestCase1() {
	print("TestCase 1: default assignment");

	int i = 1;

	print("i = " + i);

	i = i + 1;

	print("i = " + i);

	return i == 2;
}

public bool TestCase2() {
	print("TestCase 2: +=");

	int i = 1;

	print("i = " + i);

	i += 1;

	print("i = " + i);

	return i == 2;
}

public bool TestCase3() {
	print("TestCase 3: -=");

	int i = 2;

	print("i = " + i);

	i -= 1;

	print("i = " + i);

	return i == 1;
}

public bool TestCase4() {
	print("TestCase 4: *=");

	int i = 2;

	print("i = " + i);

	i *= 2;

	print("i = " + i);

	return i == 4;
}

public bool TestCase5() {
	print("TestCase 5: /=");

	int i = 2;

	print("i = " + i);

	i /= 2;

	print("i = " + i);

	return i == 1;
}

